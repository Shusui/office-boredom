#ifndef TILE_HPP
#define TILE_HPP

#include <SFML/Graphics.hpp>

#include "Game.hpp"

enum TileType {
  GROUND = 0,
  WALL = 1,
};

class Tile {
  private:
    Game *game;

    int x;
    int y;
    int tileSize;
    
    sf::Texture *texture;

  public:
    Tile(Game *_game, int _x, int _y, int _tileSize, int _type);
    Tile(Game *_game, int _type, char tileName[]);

    TileType type;
    int drawType;
    sf::Sprite sprite;
};

#endif
