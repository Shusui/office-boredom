#ifndef TILE_HPP
#define TILE_HPP

#include <SFML/Graphics.hpp>

enum TileType {
  GROUND = 0,
  WALL = 1,
};

class Tile {
  private:
    sf::Texture texture;
    
  public:
    Tile(int _type);
    Tile(int _type, char tileName[]);
    
    TileType type;
    sf::Sprite sprite;
};

#endif
