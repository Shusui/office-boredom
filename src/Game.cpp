#include "Game.hpp"
#include "TitleState.hpp"

Game::Game() {
  title = "Office Boredom";
  window.create(sf::VideoMode(640, 480, 1), title.c_str(),
                sf::Style::Titlebar | sf::Style::Close);

  window.setFramerateLimit(60);
  window.setPosition(
    sf::Vector2i(sf::VideoMode::getDesktopMode().width / 2 - 500,
                 sf::VideoMode::getDesktopMode().height / 2 - 320));

  windowFocused = true;

  arialFont.loadFromFile("res/arial.ttf");

  srand(time(NULL));

  currentState = new TitleState(this);
  lastTime = 0;
}

void Game::run() {
  currentState->setup();

  while (window.isOpen()) {
    sf::Event event;

    scrolledUp = false;
    scrolledDown = false;

    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }

      if (event.type == sf::Event::LostFocus) {
        windowFocused = false;
      }

      if (event.type == sf::Event::GainedFocus) {
        windowFocused = true;
      }

      if (event.type == sf::Event::MouseWheelMoved)
      {
        if (event.mouseWheel.delta > 0)
        {
          scrolledUp = true;
        }
        else if (event.mouseWheel.delta < 0)
        {
          scrolledDown = true;
        }
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

int main(int argc, char *argv[]) {
  Game *game = new Game();
  game->run();

  return 0;
}
