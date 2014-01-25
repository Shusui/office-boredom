#include "Tile.hpp"

Tile::Tile(int _type) {
  type = static_cast<TileType>(_type);
  texture.loadFromFile("res/tile" + std::to_string(type) + ".png");
  sprite.setTexture(texture);
}

Tile::Tile(int _type, char tileName[]) {
  char buffer[200];
  type = static_cast<TileType>(_type);
  printf("%s\n", tileName);
  sprintf(buffer, "res/tile%s.png", tileName);
  printf("%s\n", buffer);
  texture.loadFromFile(buffer);
  sprite.setTexture(texture);
}
