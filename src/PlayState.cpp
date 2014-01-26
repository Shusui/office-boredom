#include "PlayState.hpp"
#include "TitleState.hpp"

PlayState::PlayState(Game *_game) {
  game = _game;
  windowWidth = game->window.getSize().x;
  windowHeight = game->window.getSize().y;

  /* Set up FPS string */
  gameClockText.setFont(game->pixelFont);
  gameClockText.setCharacterSize(12);
  gameClockText.setPosition(windowWidth - 28, 2);
  gameClockText.setColor(sf::Color::White);

  /* Set up player, map and other stuff */
  currentLevel = 1;

  setup();
}

void PlayState::setup() {
  if (currentLevel > game->findNumberOfMaps()) {
    game->currentState = new GameOverState(game, 2);
    return;
  }

  char tempFileName[20];
  sprintf(tempFileName, "res/level%d.txt", currentLevel);
  tilemap = new Tilemap(game, tempFileName, 20, 15);
  player = new Player(game, this);

  gameClock.restart();

  canGoNextLevel = true;
  canGoPreviousLevel = true;

  hasBegun = false;
  beginClock.restart();
}

void PlayState::addEnemies() {
  enemies.clear();
  maxEnemies = 10;
  for (int i = 0; i < maxEnemies; i++) {
    if(i<maxEnemies*0.3)
      enemies.push_back(new Enemy(game, this, false));
    else
      enemies.push_back(new Enemy(game, this, true));
  }
}

void PlayState::update() {
  player->update();
  
  for (int i = 0; i < (int) enemies.size(); i++) {
    enemies[i]->update();
  }

  int countDownSeconds = 90 - gameClock.getElapsedTime().asSeconds();
  gameClockString = std::to_string((int) floor(countDownSeconds / 60)) + ":"
    + std::to_string((int) (countDownSeconds - floor(countDownSeconds / 60) * 60));

  if (countDownSeconds <= 0) {
    player->satisfactionSound.stop();
    game->currentState = new GameOverState(game, 1);
  }

  int beginCountDown = 3 - beginClock.getElapsedTime().asSeconds();

  if (beginCountDown <= 0 && !hasBegun) {
    addEnemies();
    beginCountDown = 10;
    hasBegun = true;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
    sf::Time delayTime = sf::seconds(0.5f);
    sf::sleep(delayTime);

    game->currentState = new TitleState(game);
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    if (canGoPreviousLevel && currentLevel != 1) {
      currentLevel--;
      setup();
      canGoPreviousLevel = false;
    }
  } else {
    canGoPreviousLevel = true;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    if (canGoNextLevel && currentLevel != game->findNumberOfMaps()) {
      currentLevel++;
      setup();
      canGoNextLevel = false;
    }
  } else {
    canGoNextLevel = true;
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
