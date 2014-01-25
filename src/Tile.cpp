#include "Tile.hpp"

Tile::Tile(Game *_game, int _type) {
  game = _game;

  type = static_cast<TileType>(_type);
  texture = game->myTextureFactory.findTexture("tile" + std::to_string(_type));

  sprite.setTexture(*texture);
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
