#include "container/circular_container.hpp"

namespace container {
  CircularContainer& CircularContainer::setRadius(float radius){
    this->radius = radius;
    return *this;
  }

  CircularContainer& CircularContainer::setPosition(float x_position, float y_position){
    this->position = sf::Vector2f{x_position, y_position};
    return *this;
  }

  CircularContainer& CircularContainer::setColor(sf::Color color){
    this->color = color;
    return *this;
  }
  
  auto CircularContainer::build() -> CircularContainer&{return *this;}
  auto CircularContainer::getOrigin() -> sf::Vector2f{return {radius, radius};}
  auto CircularContainer::getPosition() -> sf::Vector2f{return position;}
  auto CircularContainer::getRadius() -> float{return radius;}
  auto CircularContainer::getColor() -> sf::Color{return color;}
}