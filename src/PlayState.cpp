#include "PlayState.hpp"

PlayState::PlayState(Game *_game) {
  game = _game;
  windowWidth = game->window.getSize().x;
  windowHeight = game->window.getSize().y;

  /* Set up FPS string */
  gameClockText.setFont(game->arialFont);
  gameClockText.setCharacterSize(12);
  gameClockText.setPosition(windowWidth - 28, 2);
  gameClockText.setColor(sf::Color::White);

  /* Set up player, map and other stuff */
  tilemap = new Tilemap(game, "res/level1.txt", 20, 15);
  player = new Player(game,this);

  activeEnemies = 0;
  spawnCoolDown = 0;

  gameClock.restart();
}

void PlayState::setup() {

}

void PlayState::update() {
  if (activeEnemies < 10 && spawnCoolDown == 0) {
    srand(time(NULL));
    enemies[activeEnemies] = new Enemy(this,rand() % 400 + 200, rand() % 300 + 100);
    activeEnemies++;
    spawnCoolDown = 120;
  }

  player->update();

  for (int i = 0; i < activeEnemies; i++) {
    enemies[i]->update();
  }

  if (spawnCoolDown > 0) {
    spawnCoolDown--;
  }

  int countDownSeconds = 120 - gameClock.getElapsedTime().asSeconds();
  gameClockString = std::to_string((int) floor(countDownSeconds / 60)) + ":"
    + std::to_string((int) (countDownSeconds - floor(countDownSeconds / 60) * 60));
}

void PlayState::draw() {
  /* Clear the screen */
  game->window.clear();

  tilemap->draw();
  game->window.draw(player->sprite);
  game->window.draw(player->satisfactionOutline);
  game->window.draw(player->satisfactionFill);
  
  for (int i = 0; i < activeEnemies; i++) {
    game->window.draw(enemies[i]->sprite);
  }

  gameClockText.setString(gameClockString);
  game->window.draw(gameClockText);

  /* Display */
  game->window.display();
}
