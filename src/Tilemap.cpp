#include "Tilemap.hpp"

Tilemap::Tilemap(Game *_game, const char *_fileName, int _width, int _height) {
  game = _game;
  width = _width;
  height = _height;
  tileSize = 32;
  fileName = _fileName;

  FILE *mapFile = fopen(fileName, "r");

  int x, y;
  for (y = 0; y < height; y++) {
    for (x = 0; x < width; x++) {
      fscanf(mapFile, "%2d", &tempMap[y][x]);
    }

    fscanf(mapFile, "\n"); // Skip newlines
  }

  int currentTileType;
  for (y = 0; y < height; y++) {
    for (x = 0; x < width; x++) {
      currentTileType = tempMap[y][x];
      
      if (currentTileType == WALL) {
        currentTileType = getWallType(x, y);
      }

      rawMap[y][x] = new Tile(game, x, y, tileSize, currentTileType);
    }
  }
  
  fclose(mapFile);
}

void Tilemap::writeToFile() {
  printf("Writing to file\n");
  
  FILE *mapFile = fopen(fileName, "w");

  int x, y;
  for (y = 0; y < height; y++) {
    for (x = 0; x < width; x++) {
      fprintf(mapFile, "%2d", tempMap[y][x]);
    }

    fprintf(mapFile, "\n");
  }

  fclose(mapFile);
}

void Tilemap::fixTiles() {
  int x, y;
  for (y = 0; y < height; y++) {
    for (x = 0; x < width; x++) {
      if (tempMap[y][x] == 1) {
        rawMap[y][x] = new Tile(game, x, y, tileSize, getWallType(x, y));
      } else {
        rawMap[y][x] = new Tile(game, x, y, tileSize, 0);
      }
    }
  }
}

int Tilemap::getWallType(int x, int y) {
  if (x == 0 && y == 0) {
    return 8;
  } else if (y == 0 && x != 0 && x != width - 1) {

    if (tempMap[y + 1][x] == 1) {
      return 12;
    }
    
    return 2;
  } else if (y == 0 && x == width - 1) {
    return 9;
  } else if (x == 0 && y != 0 && y != height - 1) {

    if (tempMap[y][x + 1] == 1) {
      return 23;
    }
    
    return 6;
  } else if (x == width - 1 && y != 0 && y != height - 1) {

    if (tempMap[y][x - 1]) {
      return 9;
    }
    
    return 7;
  } else if (x == 0 && y == height - 1) {
    return 5;
  } else if (y == height - 1 && x != 0 && x != width - 1) {

    if (tempMap[y - 1][x] == 1) {
      return 11;
    }
    
    return 10;
  } else if (x == width - 1 && y == height - 1) {
    return 4;
  } else {

    if (tempMap[y - 1][x] == 0 && tempMap[y + 1][x] == 0
        && tempMap[y][x - 1] == 0 && tempMap[y][x + 1] == 0) {
      return 14;
    } else if (tempMap[y - 1][x] == 0 && tempMap[y + 1][x] == 0
               && tempMap[y][x - 1] == 0 && tempMap[y][x + 1] == 1) {
      return 18;
    } else if (tempMap[y - 1][x] == 0 && tempMap[y + 1][x] == 0
               && tempMap[y][x - 1] == 1 && tempMap[y][x + 1] == 0) {
      return 21;
    } else if (tempMap[y - 1][x] == 0 && tempMap[y + 1][x] == 0
               && tempMap[y][x - 1] == 1 && tempMap[y][x + 1] == 1) {
      return 17;
    } else if (tempMap[y - 1][x] == 0 && tempMap[y + 1][x] == 1
               && tempMap[y][x - 1] == 0 && tempMap[y][x + 1] == 0) {
      return 24;
    } else if (tempMap[y - 1][x] == 1 && tempMap[y + 1][x] == 1
               && tempMap[y][x - 1] == 1 && tempMap[y][x + 1] == 0) {
      return 19;
    } else if (tempMap[y - 1][x] == 1 && tempMap[y + 1][x] == 0
               && tempMap[y][x - 1] == 0 && tempMap[y][x + 1] == 1) {
      return 15;
    } else if (tempMap[y - 1][x] == 0 && tempMap[y + 1][x] == 1
               && tempMap[y][x - 1] == 1 && tempMap[y][x + 1] == 0) {
      return 20;
    } else if (tempMap[y - 1][x] == 1 && tempMap[y + 1][x] == 1
        && tempMap[y][x - 1] == 0 && tempMap[y][x + 1] == 0) {
      return 3;
    } else if (tempMap[y - 1][x] == 1 && tempMap[y + 1][x] == 0
               && tempMap[y][x - 1] == 0 && tempMap[y][x + 1] == 0) {
      return 13;
    } else if (tempMap[y - 1][x] == 0 && tempMap[y + 1][x] == 1
               && tempMap[y][x - 1] == 1 && tempMap[y][x + 1] == 1) {
      return 25;
    } else if (tempMap[y - 1][x] == 1 && tempMap[y + 1][x] == 1
               && tempMap[y][x - 1] == 1 && tempMap[y][x + 1] == 1) {
      return 26;
    } else if (tempMap[y - 1][x] == 1 && tempMap[y + 1][x] == 0
               && tempMap[y][x - 1] == 1 && tempMap[y][x + 1] == 0) {
      return 16;
    } else if (tempMap[y - 1][x] == 0 && tempMap[y + 1][x] == 1
               && tempMap[y][x - 1] == 0 && tempMap[y][x + 1] == 1) {
      return 27;
    }

    return 1;
  }
}

void Tilemap::draw() {
  int x, y;
  for (y = 0; y < height; y++) {
    for (x = 0; x < width; x++) {
      game->window.draw(rawMap[y][x]->sprite);
    }
  }
}
