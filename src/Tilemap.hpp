#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#define MAX_WIDTH 64
#define MAX_HEIGHT 64

#include <stdio.h>

#include "Game.hpp"
#include "Tile.hpp"

class Tilemap {
  private:
    int getWallType(int x, int y);
    
    Game *game;

    int tempMap[MAX_HEIGHT][MAX_WIDTH];
    
  public:
    Tilemap(Game *_game, const char *fileName, int _width, int _height);
    void draw();

    Tile *rawMap[MAX_HEIGHT][MAX_WIDTH];
    int width;
    int height;
    int tileSize;
};

#endif
