#include "Tilemap.hpp"

Tilemap::Tilemap(Game *_game, const char *fileName, int width, int height) {
  game = _game;
  
  FILE *mapFile = fopen(fileName, "r");
  
  int x, y;
  for (y = 0; y < height; y++) {
    for (x = 0; x < width; x++) {
      fscanf(mapFile, "%d", &rawMap[y][x]);
    }

    fscanf(mapFile, "\n"); // Skip newlines
  }

  fclose(mapFile);

  tileSize = 32;
}

void Tilemap::draw() {
  int x, y;
  for (y = 0; y < height; y++) {
    for (x = 0; x < width; x++) {
      sf::RectangleShape rectangle;
      rectangle.setSize(sf::Vector2f(tileSize, tileSize));
      rectangle.setPosition(x * tileSize, y * tileSize);
      
      if (rawMap[y][x] == 0) {
        rectangle.setFillColor(sf::Color::Black);
      } else if (rawMap[y][x] == 1) {
        rectangle.setFillColor(sf::Color::White);
      }

      game->window.draw(rectangle);
    }
  }
}
