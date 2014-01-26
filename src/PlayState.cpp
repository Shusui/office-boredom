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
  player = new Player(game, this);

  activeEnemies = 0;
  spawnCoolDown = 0;

  gameClock.restart();

  //std::string spriteNameArray[] = {"res/desk.png", "res/tile1.png", "res/tilewall_14.png", "res/tilewall_19.png", "res/tilewall_4.png", "res/tilewall_9.png", "res/enemy.png",   "res/tilewall_10.png",  "res/tilewall_15.png",  "res/tilewall_1.png", "res/tilewall_5.png", "res/heart.png", "res/tilewall_11.png", "res/tilewall_16.png", "res/tilewall_20.png", "res/tilewall_6.png", "res/player.png", "res/tilewall_12.png", "res/tilewall_17.png", "res/tilewall_2.png", "res/tilewall_7.png", "res/tile0.png", "res/tilewall_13.png", "res/tilewall_18.png", "res/tilewall_3.png", "res/tilewall_8.png"};
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

  if (countDownSeconds <= 0) {
    game->currentState = new GameOverState(game, 1);
  }
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
