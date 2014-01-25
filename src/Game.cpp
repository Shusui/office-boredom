#include "Game.hpp"

Game::Game()
{
  title = "Office Boredom";
  window.create(sf::VideoMode(1000, 640, 1), title.c_str(),
                sf::Style::Titlebar | sf::Style::Close);

  window.setFramerateLimit(60);
  window.setPosition(
    sf::Vector2i(sf::VideoMode::getDesktopMode().width / 2 - 500,
                 sf::VideoMode::getDesktopMode().height / 2 - 320));

  windowFocused = true;

  currentState = new PlayState(this);
  lastTime = 0;
}

void Game::run()
{
  currentState->setup();

  while (window.isOpen())
  {
    sf::Event event;

    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
      {
        window.close();
      }

      if (event.type == sf::Event::LostFocus)
      {
        windowFocused = false;
      }

      if (event.type == sf::Event::GainedFocus)
      {
        windowFocused = true;
      }
    }

    currentState->update();
    currentState->draw();

    float currentTime = deltaClock.restart().asSeconds();
    dt = currentTime - lastTime;
    fps = 1.f / currentTime;
    lastTime = currentTime;
  }
}

int main(int argc, char *argv[])
{
  Game *game = new Game();
  game->run();

  return 0;
}
