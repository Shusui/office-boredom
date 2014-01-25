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

  /* Set up player */
  player = new Player();
}

void PlayState::setup() {

}

void PlayState::update() {
  sf::Vector2i mouse = sf::Mouse::getPosition(game->window);

  player->update();
}

void PlayState::draw() {
  /* Clear the screen */
  game->window.clear();

  /* Draw FPS */
  stringstream fpsStream;
  fpsStream << ceil(game->fps) << " fps";
  fps.setString(fpsStream.str());
  game->window.draw(fps);

  game->window.draw(player->sprite);

  /* Display */
  game->window.display();
}
