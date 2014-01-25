#include "Tilemap.hpp"

Tilemap::Tilemap(const char *fileName, int width, int height) {
  FILE *mapFile = fopen(fileName, "r");

  int x, y;
  for (y = 0; y < height; y++) {
    for (x = 0; x < width; x++) {
      fscanf(mapFile, "%d", &rawMap[y][x]);
    }

    fscanf(mapFile, "\n"); // Skip newlines
  }

  fclose(mapFile);
}

void Tilemap::draw() {
  
}
