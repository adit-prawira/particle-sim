#pragma once
#include <vector>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "logger/logger.hpp"

namespace entities {
  class Particle {
    public:
      Particle& setColor(sf::Color color);
      Particle& setInitialPosition(float x_position, float y_position);
      Particle& setPosition(float x_position, float y_position);
      Particle& setRadius(float radius);
      Particle& build();

      float getRadius();
      sf::Vector2f getPosition();
      sf::Vector2f getOrigin();

      sf::Color getColor();
      void updatePosition(float delta_time);
      void accelerate(float x_acceleration, float y_acceleration);
      sf::Vector2f position;

    private:
      float radius;
      sf::Color color;
      sf::Vector2f previous_position;
      sf::Vector2f velocity;
      sf::Vector2f acceleration;
      std::string compileValidations(std::vector<std::string> validation_messages);
      logger::Logger logger;
  };
}