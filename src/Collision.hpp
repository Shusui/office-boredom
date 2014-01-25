#ifndef COLLISION_HPP
#define COLLISION_HPP

#include <stdio.h>
#include <SFML/Graphics.hpp>

class Collision {
  private:

  public:
		virtual bool checkCollision(sf::FloatRect);
};

#endif
