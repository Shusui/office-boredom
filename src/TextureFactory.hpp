#ifndef SPRITE_FACTORY_HPP
#define SPRITE_FACTORY_HPP

#include <stdio.h>
#include <map>
#include <list>

#include <SFML/Graphics.hpp>

class TextureFactory {
  private:
    sf::Texture *loadTexture(std::string fileName);

    sf::Texture textureVector[100];
    int textureVectorSize;
    std::map<std::string, int> textureMap;

  public:
    TextureFactory();
    
    sf::Texture *findTexture(std::string textureName);
};

#endif
