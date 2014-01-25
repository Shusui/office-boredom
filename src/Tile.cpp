#include "Tile.hpp"

Tile::Tile(int _type) {
  type = static_cast<TileType>(_type);
  texture.loadFromFile("res/tile" + std::to_string(type) + ".png");
  sprite.setTexture(texture);
}
