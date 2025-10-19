#pragma once
#include "constants/constant.hpp"
#include "entities/particle.hpp"
#include "engine/physics_engine.hpp"
#include <SFML/Graphics.hpp>

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
  };
}