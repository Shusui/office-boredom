#include "Tilemap.hpp"

Tilemap::Tilemap(Game *_game, const char *fileName, int _width, int _height) {
  game = _game;
  width = _width;
  height = _height;
  tileSize = 32;

  FILE *mapFile = fopen(fileName, "r");

  int x, y, currentTile;
  for (y = 0; y < height; y++) {
    for (x = 0; x < width; x++) {
      fscanf(mapFile, "%1d", &currentTile);
      rawMap[y][x] = new Tile(currentTile);
      rawMap[y][x]->sprite.setPosition(x * tileSize, y * tileSize);
    }

    fscanf(mapFile, "\n"); // Skip newlines
  }

  printf("\n");
  
  fclose(mapFile);
}

void Tilemap::draw() {
  int x, y;
  for (y = 0; y < height; y++) {
    for (x = 0; x < width; x++) {
      game->window.draw(rawMap[y][x]->sprite);
    }
  }
}
