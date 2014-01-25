#include "Tilemap.hpp"

Tilemap::Tilemap(Game *_game, const char *fileName, int _width, int _height) {
  game = _game;
  width = _width;
  height = _height;
  tileSize = 32;

  FILE *mapFile = fopen(fileName, "r");

  int x, y;
  for (y = 0; y < height; y++) {
    for (x = 0; x < width; x++) {
      fscanf(mapFile, "%1d", &rawMap[y][x]);

      map[y][x] = sf::RectangleShape();
      map[y][x].setSize(sf::Vector2f(tileSize, tileSize));
      map[y][x].setPosition(x * tileSize, y * tileSize);

      if(rawMap[y][x] == 0) {
        sf::Color grayColor = sf::Color(211, 211, 211);
        map[y][x].setFillColor(grayColor);
      } else if (rawMap[y][x] == 1) {
        map[y][x].setFillColor(sf::Color::Black);
      }
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
      game->window.draw(map[y][x]);
    }
  }
}
