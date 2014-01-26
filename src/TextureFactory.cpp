#include "TextureFactory.hpp"

TextureFactory::TextureFactory() {
  textureVectorSize = 0;
}

sf::Texture *TextureFactory::loadTexture(std::string fileName) {
  std::string fullFileName = "res/" + fileName + ".png";

  sf::Texture texture;
  texture.loadFromFile(fullFileName);
  textureVector[textureVectorSize++] = texture;

  textureMap[fileName] = textureVectorSize - 1;

  return &(textureVector[textureVectorSize - 1]);
}

sf::Texture *TextureFactory::findTexture(std::string textureName) {
  if (textureMap.find(textureName) != textureMap.end()) {
    return &(textureVector[textureMap[textureName]]);
  }

  return loadTexture(textureName);
}
