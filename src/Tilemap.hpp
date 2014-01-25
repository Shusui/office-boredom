#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#define MAX_WIDTH 64
#define MAX_HEIGHT 64

#include <stdio.h>

class Tilemap {
  private:
  
  public:
    Tilemap(const char *fileName, int width, int height);

    int rawMap[MAX_HEIGHT][MAX_WIDTH];
    int width;
    int height;
};

#endif
