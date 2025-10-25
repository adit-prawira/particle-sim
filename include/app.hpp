#pragma once
#include "constants/constant.hpp"
#include "entities/particle.hpp"
#include "container/circular_container.hpp"
#include "engine/physics_engine.hpp"
#include "generators/particle_generator.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

// std
#include <string>
#include <iostream>

namespace particle_sim {
  class App {
    public:
      App(const std::string name);
      void run();

    private:
      sf::RenderWindow window;
      sf::Font font;

      void draw(entities::Particle particle);
      void draw(container::CircularContainer container);
      sf::Vector2f windowCenter();
  };
}