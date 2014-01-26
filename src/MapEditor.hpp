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

    int level;

    bool canGoLeft;
    bool canGoRight;

    char fileName[20];
    
  public:
    MapEditor(Game *_game, int _level);

    void setup();
    void update();
    void draw();

    Tilemap *tilemap;
};

#endif
