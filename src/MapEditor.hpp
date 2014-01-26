#ifndef MAP_EDITOR_HPP
#define MAP_EDITOR_HPP

#include <cmath>

#include "Game.hpp"
#include "Tilemap.hpp"

class MapEditor : public State {
  private:
    int findNumberOfMaps();

    Game *game;

    bool canWriteFile;
    bool canNewFile;

  public:
    MapEditor(Game *_game);

    void setup();
    void update();
    void draw();

    Tilemap *tilemap;
};

#endif
