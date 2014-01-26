#include "Tile.hpp"

Tile::Tile(Game *_game, int _x, int _y, int _tileSize, int _type) {
  game = _game;
  x = _x;
  y = _y;
  tileSize = _tileSize;
  
  drawType = _type;
  type = static_cast<TileType>(_type >= 1);
  texture = game->myTextureFactory.findTexture("tile" + std::to_string(_type));

  sprite.setTexture(*texture);
  sprite.setPosition(x * tileSize, y * tileSize);
}

Tile::Tile(Game *_game, int _type, char tileName[]) {
  char buffer[200];
  type = static_cast<TileType>(_type);
  printf("%s\n", tileName);
  sprintf(buffer, "res/tile%s.png", tileName);
  printf("%s\n", buffer);

  texture = game->myTextureFactory.findTexture(buffer);

  sprite.setTexture(*texture);
}
