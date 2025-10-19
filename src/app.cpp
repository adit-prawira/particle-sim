#include <app.hpp>

namespace particle_sim {
  App::App(const std::string name):
    window(sf::VideoMode({constants::WINDOW_WIDTH, constants::WINDOW_HEIGHT}), name), 
    font("fonts/FiraCode-Regular.ttf") {}

  void App::run(){
    this->window.setFramerateLimit(constants::FRAME_LIMIT);
    std::cout << "STARTING: Initiating particle simulation..."<<std::endl;
    entities::Particle particle;
    particle
      .setRadius(10)
      .setPosition(100.0f,100.0f)
      .setColor(sf::Color::White)
      .build();

    engine::PhysicsEngine physics_engine;
    physics_engine
      .setFrameRate(constants::FRAME_LIMIT)
      .setSteps(1)
      .build();

    while(this->window.isOpen()){
      while(const std::optional event = this->window.pollEvent()){
        if(event->is<sf::Event::Closed>()){
          std::cout << "EXITING: Closing particle simulation window..." <<std::endl;
          this->window.close();
        }
      }
      this->window.clear(sf::Color::Black);
      this->draw(particle);

      physics_engine.applyGravity(particle);
      physics_engine.updatePosition(particle);
  
      this->window.display();
    }
  }

  // Private
  void App::draw(entities::Particle particle){
      sf::CircleShape circle;
      circle.setRadius(particle.getRadius());
      circle.setPosition(sf::Vector2f{particle.getPosition().x, particle.getPosition().y});
      circle.setFillColor(sf::Color::White);
      this->window.draw(circle);
  }
}