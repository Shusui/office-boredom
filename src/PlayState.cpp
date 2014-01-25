#include "PlayState.hpp"

PlayState::PlayState(Game *_game)
{
  game = _game;
  windowWidth = game->window.getSize().x;
  windowHeight = game->window.getSize().y;

  /* Set up FPS string */
  fps.setFont(game->arialFont);
  fps.setCharacterSize(12);
  fps.setPosition(2, 2);
  fps.setColor(sf::Color::White);
}

void PlayState::setup()
{

}

void PlayState::update()
{
  sf::Vector2i mouse = sf::Mouse::getPosition(game->window);

}

void PlayState::draw()
{
  /* Clear the screen */
  game->window.clear();

  /* Draw FPS */
  stringstream fpsStream;
  fpsStream << ceil(game->fps) << " fps";
  fps.setString(fpsStream.str());
  game->window.draw(fps);

  /* Display */
  game->window.display();
}
