#include "MapEditor.hpp"
#include "TitleState.hpp"

MapEditor::MapEditor(Game *_game, int _level) {
  game = _game;
  level = _level;

  sprintf(fileName, "res/level%d.txt", level);
  tilemap = new Tilemap(game, fileName, 20, 15);

  canWriteFile = true;
  canNewFile = true;

  canGoLeft = true;
  canGoRight = true;
}

void MapEditor::setup() {

}

void MapEditor::update() {
  sf::Vector2i mouse = sf::Mouse::getPosition(game->window);

  sf::Vector2i currentTile;
  currentTile.x = (int) floor(mouse.x / tilemap->tileSize);
  currentTile.y = (int) floor(mouse.y / tilemap->tileSize);

  if (game->scrolledUp) {
    tilemap->tempMap[currentTile.y][currentTile.x] = 1;
    tilemap->fixTiles();
  } else if (game->scrolledDown) {
    tilemap->tempMap[currentTile.y][currentTile.x] = 0;
    tilemap->fixTiles();
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
    if (canWriteFile) {
      tilemap->writeToFile();
      canWriteFile = false;
    }
  } else {
    canWriteFile = true;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::N)) {
    if (canNewFile) {
      sprintf(fileName, "res/level%d.txt", game->findNumberOfMaps() + 1);

      FILE *newMapFile = fopen(fileName, "w");

      int width = 20;
      int height = 15;

      int x, y;
      for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
          if (x == 0 || x == width - 1 || y == 0 || y == height - 1) {
            fprintf(newMapFile, "01");
          } else {
            fprintf(newMapFile, "00");
          }
        }

        fprintf(newMapFile, "\n");
      }

      fclose(newMapFile);

      tilemap = new Tilemap(game, fileName, width, height);

      canNewFile = false;
    }
  } else {
    canNewFile = true;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
    sf::Time delayTime = sf::seconds(0.5f);
    sf::sleep(delayTime);

    game->currentState = new TitleState(game);
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    if (level != 1) {
      if (canGoLeft) {
        sprintf(fileName, "res/level%d.txt", --level);
        tilemap = new Tilemap(game, fileName, 20, 15);

        canGoLeft = false;
      }
    }
  } else {
    canGoLeft = true;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    if (level != game->findNumberOfMaps()) {
      if (canGoRight) {
        sprintf(fileName, "res/level%d.txt", ++level);
        tilemap = new Tilemap(game, fileName, 20, 15);

        canGoRight = false;
      }
    }
  } else {
    canGoRight = true;
  }
}

void MapEditor::draw() {
  game->window.clear();

  tilemap->draw();

  game->window.display();
}
