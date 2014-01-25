#include "Enemy.hpp"
#include "PlayState.hpp"

Enemy::Enemy(PlayState *_state,float _x, float _y) {
  state = _state;
  x = _x;
  y = _y;
  srand(time(NULL));
  speedX = rand() % 4 + 1;
  speedY = rand() % 5 + 1;

  texture.loadFromFile("res/enemy.png");
  sprite.setTexture(texture);
  sprite.setScale(0.5,0.5);
  sprite.setPosition(x,y);
}

void Enemy::update() {
  float old_x = x;
  float old_y = y;

  x += speedX;
  y += speedY;

  wallCollision(old_x,old_y);

  /*if (x < 0) {
    x = 0;
    speedX *= (-1);
  } else if (x > 608) {
    x = 608;
    speedX *= (-1);
  }

  if (y < 0) {
    y = 0;
    speedY *= (-1);
  } else if (y > 448) {
    y = 448;
    speedY *= (-1);
  }*/

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

void Enemy::pathToTarget(){
  sf::Vector2f target;
  target.x = state->player->sprite.getPosition().x;
  target.y = state->player->sprite.getPosition().y;

  vector<sf::Vector2f> openset;
  vector<sf::Vector2f> closedset;
  vector<float> fscore;
  vector<float> gscore;

  sf::Vector2f tmp;
  tmp.x = x;
  tmp.y = y;
  openset.push_back(tmp);
  //Need function to calculate distance
  fscore.push_back(1);
  gscore.push_back(0);

  while(openset.size()>0){
    int min = fscore[0];
    int idx = 0;
    for(int i=1;i<(int)fscore.size();i++){
      if(fscore[i] < min){
        min = fscore[i];
        idx = i;
      }
    }
    sf::Vector2f current;
    current.x = openset[idx].x;
    current.y = openset[idx].y;

    for(y = current.y-1; y <= current.y+1;y++){
      for(x = current.x-1; x <= current.x+1;x++){
         
      }
    }

    
 
  }

}

