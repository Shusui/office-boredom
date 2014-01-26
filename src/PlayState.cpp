#include "PlayState.hpp"
#include "TitleState.hpp"

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
  tilemap = new Tilemap(game, "res/level2.txt", 20, 15);
  player = new Player(game, this);

  gameClock.restart();

  maxEnemies = 10;
  for (int i = 0; i < maxEnemies; i++) {
    enemies.push_back(new Enemy(game,this));
  }
}

void PlayState::setup() {

}

void PlayState::update() {
  player->update();

  for (int i = 0; i < (int) enemies.size(); i++) {
    enemies[i]->update();
  }

  int countDownSeconds = 120 - gameClock.getElapsedTime().asSeconds();
  gameClockString = std::to_string((int) floor(countDownSeconds / 60)) + ":"
    + std::to_string((int) (countDownSeconds - floor(countDownSeconds / 60) * 60));

  if (countDownSeconds <= 0) {
    game->currentState = new GameOverState(game, 1);
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
    sf::Time delayTime = sf::seconds(0.5f);
    sf::sleep(delayTime);

    game->currentState = new TitleState(game);
  }
}

void PlayState::draw() {
  /* Clear the screen */
  game->window.clear();

  tilemap->draw();
  game->window.draw(player->sprite);
  game->window.draw(player->satisfactionFill);

  for (int i = 0; i < (int) enemies.size(); i++) {
    game->window.draw(enemies[i]->sprite);
  }

  gameClockText.setString(gameClockString);
  game->window.draw(gameClockText);

  /* Display */
  game->window.display();
}
