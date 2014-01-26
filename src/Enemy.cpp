#include "Enemy.hpp"
#include "PlayState.hpp"
#include <math.h>

Enemy::Enemy(Game *_game,PlayState *_state,bool _followPlayer) {
  state = _state;
  game = _game;
  followPlayer = _followPlayer;
  speedX = (rand() % 3000 - 1500)/(float)1000;
  speedY = (rand() % 3000 - 1500)/(float)1000;

  texture.loadFromFile("res/enemy.png");
  sprite.setTexture(texture);
  sprite.setScale(0.5,0.5);
  
  do {
    x = (int)(rand() % state->tilemap->width);
    y = (int)(rand() % state->tilemap->height);
  } while (state->tilemap->rawMap[(int) y][(int) x]->type != GROUND);
  x *= state->tilemap->tileSize;
  y *= state->tilemap->tileSize;
  sprite.setPosition(x,y);

  searchPlayerClock.restart();
  randomMoveClock.restart();
}

void Enemy::update() {
  float old_x = x;
  float old_y = y;

  int searchPlayerCountdown = 400 - searchPlayerClock.getElapsedTime().asMilliseconds();
  if(searchPlayerCountdown<=0){
    if(abs(state->player->sprite.getPosition().x-x)<100 && abs(state->player->sprite.getPosition().y-y)<100)
      path = pathToTarget();
    //printf("%d\n",(int)path.size());
    searchPlayerClock.restart();
  }

  if((int)path.size()>0){
    //printf("%d\n",(int)path.size());
    if((int)path.size()<50 && state->player->isSatisfying){
      game->currentState = new GameOverState(game,0);
      state->player->satisfactionSound.stop();
    }
     
    if(followPlayer){ 
      x = path[(int)path.size()-1].x;
      y = path[(int)path.size()-1].y;
      path.erase(path.end()-1);
      sprite.setPosition(x, y);
      return;
    }
  }

  int randomMoveCountdown = 5000 - randomMoveClock.getElapsedTime().asMilliseconds();
  if(randomMoveCountdown<=0){
    do{
      speedX = (rand() % 3000 - 1500)/(float)1000;
      speedY = (rand() % 3000 - 1500)/(float)1000;
    } while(speedY==0 && speedX==0);
    randomMoveClock.restart();
  }


  x += speedX;
  y += speedY;

  /*if((int)path.size()==0)
    return;
  x = path[(int)path.size()-1].x;
  y = path[(int)path.size()-1].y;
  path.erase(path.end()-1);*/
  wallCollision(old_x,old_y);
  sprite.setPosition(x, y);
}

bool Enemy::checkCollision(sf::FloatRect other) {
  return sprite.getGlobalBounds().intersects(other);
}

void Enemy::wallCollision(float old_x, float old_y){
  sprite.setPosition(x, old_y);
  for(int ty = 0;ty < state->tilemap->height;ty++){
    for(int tx = 0;tx < state->tilemap->width; tx++){
      if(state->tilemap->rawMap[ty][tx]->type==WALL &&
         this->checkCollision(state->tilemap->rawMap[ty][tx]->sprite.getGlobalBounds())){
        if(x>old_x){
          x = state->tilemap->rawMap[ty][tx]->sprite.getPosition().x - sprite.getLocalBounds().width*sprite.getScale().x;
        } else if(x<old_x){
          x = state->tilemap->rawMap[ty][tx]->sprite.getPosition().x+state->tilemap->tileSize;
        } else {
          x = old_x;
        }
        speedX = speedX*(-1);
        return; 
      }
    }
  }
  
  sprite.setPosition(old_x, y);
  for(int ty = 0;ty < state->tilemap->height;ty++){
    for(int tx = 0;tx < state->tilemap->width; tx++){
      if(state->tilemap->rawMap[ty][tx]->type==WALL &&
         this->checkCollision(state->tilemap->rawMap[ty][tx]->sprite.getGlobalBounds())){
        if(y>old_y){
          y = state->tilemap->rawMap[ty][tx]->sprite.getPosition().y - sprite.getLocalBounds().height*sprite.getScale().y;
        } else if(y<old_y){
          y = state->tilemap->rawMap[ty][tx]->sprite.getPosition().y+state->tilemap->tileSize;
        } else {
          y = old_y;
        }
        speedY *= (-1);
        return;  
      }
    }
  }
  sprite.setPosition(x, y);
  for(int ty = 0;ty < state->tilemap->height;ty++){
    for(int tx = 0;tx < state->tilemap->width; tx++){
      if(state->tilemap->rawMap[ty][tx]->type==WALL &&
         this->checkCollision(state->tilemap->rawMap[ty][tx]->sprite.getGlobalBounds())){
        if(x>old_x){
          x = state->tilemap->rawMap[ty][tx]->sprite.getPosition().x - sprite.getLocalBounds().width*sprite.getScale().x;
        } else if(x<old_x){
          x = state->tilemap->rawMap[ty][tx]->sprite.getPosition().x+state->tilemap->tileSize;
        } else {
          x = old_x;
        }

        if(y>old_y){
          y = state->tilemap->rawMap[ty][tx]->sprite.getPosition().y - sprite.getLocalBounds().height*sprite.getScale().y;
        } else if(y<old_y){
          y = state->tilemap->rawMap[ty][tx]->sprite.getPosition().y+state->tilemap->tileSize;
        } else {
          y = old_y;
        }
        speedX *= (-1);
        speedY *= (-1);
        return;
      }
    }
  }

}

vector<sf::Vector2f> Enemy::reconstructPath(vector<int> came_from,vector<sf::Vector2f> set,int idx){
  vector<sf::Vector2f> p;
  while(came_from[idx]!=-1){
    p.push_back(set[idx]);
    idx = came_from[idx]; 
  }
  return p;
}

vector<sf::Vector2f> Enemy::pathToTarget(){
  int i,min,idx,my,mx;
  float tx;
  float ty;
  float speedX = 1;
  float speedY = 1;
  vector<sf::Vector2f> ret;
  sf::Vector2f target;
  target.x = floor(state->player->sprite.getPosition().x/speedX)*speedX;
  target.y = floor(state->player->sprite.getPosition().y/speedY)*speedY;
 
  if(x == target.x && y==target.y)
    return ret;

  vector<sf::Vector2f> set;
  vector<bool> closed;
  vector<float> fscore;
  vector<float> gscore;
  vector<int> came_from;

  sf::Vector2f tmp;
  tmp.x = x;
  tmp.y = y;
  set.push_back(tmp);
  closed.push_back(false);
  came_from.push_back(-1);
  //Need function to calculate distance
  fscore.push_back(abs(target.x-tmp.x)+abs(target.y-tmp.y));
  gscore.push_back(0);

  int count=0;
  while(count<=80){
    ++count;
    //printf("COUNT: %d SIZE: %d\n",count,(int)set.size());
    for(i=0;i<(int)closed.size();i++){
      if(closed[i]==false){
        idx = i;
        min = fscore[idx];
        break;
      }
    }
    //printf("IDX: %d\n",idx);
    if(i==(int)closed.size()) break;

    for(i=idx+1;i<(int)fscore.size();i++){
      if(fscore[i] < min && closed[i]==false){
        min = fscore[i];
        idx = i;
      }
    }
    //printf("IDX: %d\n",idx);
    
    if(target.x==set[idx].x && target.y==set[idx].y){
      return reconstructPath(came_from,set,idx);
    }

    sf::Vector2f current;
    current.x = floor(set[idx].x/speedX)*speedX;
    current.y = floor(set[idx].y/speedY)*speedY;
    closed[idx]=true;
  
    for(ty = current.y-speedY; ty <= current.y+speedY;ty+=speedY){
      if(ty<0) continue;
      if(ty>state->windowHeight) continue;
      for(tx = current.x-speedX; tx <= current.x+speedX;tx+=speedX){
        if(tx<0) continue;
        if(tx>state->windowWidth) continue;

        sf::FloatRect *bounds = new sf::FloatRect(tx,ty,sprite.getGlobalBounds().width,sprite.getGlobalBounds().height);
        for(my=0;my<state->tilemap->height;my++){
          for(mx=0;mx<state->tilemap->width;mx++){
            if(state->tilemap->rawMap[my][mx]->type==WALL && bounds->intersects(state->tilemap->rawMap[my][mx]->sprite.getGlobalBounds())) break;
          }
          if(mx<state->tilemap->width) break;
        }
        if(my<state->tilemap->height) continue;
         
        for(i=0;i<(int)set.size();i++){
          if(set[i].x==tx && set[i].y==ty){
            break;
          }
        }

        if(i==(int)set.size()){
          tmp.x = tx;
          tmp.y = ty;
          //Add distance function
          set.push_back(tmp);
          gscore.push_back(gscore[idx]+1);
          came_from.push_back(idx);
          fscore.push_back(abs(target.x-tmp.x)+abs(target.y-tmp.y));
          closed.push_back(false);
        }
        else if(closed[i]==true) continue;
        else if(closed[i]==false){
          float tmp_g_score = gscore[idx]+1;
          if(tmp_g_score < gscore[i]){
            gscore[i]=tmp_g_score;
            came_from[i]=idx;
            fscore[i]=abs(target.x-tmp.x)+abs(target.y-tmp.y);
            closed[i]=false;
          }
        }
      }
    }
  }
  return ret;
}

