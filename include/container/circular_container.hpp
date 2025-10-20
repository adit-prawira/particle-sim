#pragma once
#include "entities/particle.hpp"
#include <SFML/Graphics.hpp>

namespace container {
  class CircularContainer {
    public:
      CircularContainer& setRadius(float radius);
      CircularContainer& setColor(sf::Color color);
      CircularContainer& setPosition(float x_position, float y_position);
      CircularContainer& build();

      sf::Vector2f getPosition();
      float getRadius();
      sf::Color getColor();
      sf::Vector2f getOrigin();
    private:
      float radius;
      sf::Vector2f position;
      sf::Color color  = sf::Color::Black;    
        
  };
}