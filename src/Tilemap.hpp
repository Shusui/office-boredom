#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#define MAX_WIDTH 64
#define MAX_HEIGHT 64

#include <stdio.h>

#include "Game.hpp"

class Tilemap {
  private:
    Game *game;
    
  public:
    Tilemap(Game *_game, const char *fileName, int width, int height);
    void draw();

    int rawMap[MAX_HEIGHT][MAX_WIDTH];
    int width;
    int height;
    int tileSize;
};

#endif
