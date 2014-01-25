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

    sf::Texture *texture;

  public:
    Tile(Game *_game, int _type);
    Tile(Game *_game, int _type, char tileName[]);

    TileType type;
    sf::Sprite sprite;
};

#endif
