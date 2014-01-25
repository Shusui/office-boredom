#include "PlayState.hpp"

PlayState::PlayState(Game *_game) {
  game = _game;
  windowWidth = game->window.getSize().x;
  windowHeight = game->window.getSize().y;

  /* Set up FPS string */
  fps.setFont(game->arialFont);
  fps.setCharacterSize(12);
  fps.setPosition(windowWidth - 38, 2);
  fps.setColor(sf::Color::White);

  /* Set up player, map and other stuff */
  player = new Player();
  tilemap = new Tilemap(game, "res/level1.txt", 20, 15);

  activeEnemies = 0;
  spawnCooldown = 0;
}

void PlayState::setup() {

}

void PlayState::update() {
  sf::Vector2i mouse = sf::Mouse::getPosition(game->window);
  if (activeEnemies < 10 && spawnCooldown == 0) {
    srand(time(NULL));
    enemies[activeEnemies] = new Enemy(rand() % 400 + 200, rand() % 300 + 100);
    activeEnemies++;
    spawnCooldown = 120;
  }
  
  player->update();

  for (int i = 0; i < activeEnemies; i++) {
    enemies[i]->update();
  }

  if (spawnCooldown > 0) {
    spawnCooldown--;
  }
}

void PlayState::draw() {
  /* Clear the screen */
  game->window.clear();

  /* Draw FPS */
  stringstream fpsStream;
  fpsStream << ceil(game->fps) << " fps";
  fps.setString(fpsStream.str());
  game->window.draw(fps);

  tilemap->draw();
  game->window.draw(player->sprite);

  for (int i = 0; i < activeEnemies; i++) {
    game->window.draw(enemies[i]->sprite);
  }
  
  /* Display */
  game->window.display();
}
