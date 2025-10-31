#include <app.hpp>

namespace particle_sim {
  App::App(const std::string name):
    window(sf::VideoMode({constants::WINDOW_WIDTH, constants::WINDOW_HEIGHT}), name), 
    font("fonts/FiraCode-Regular.ttf") {}

  void App::run(){
    this->window.setFramerateLimit(constants::FRAME_LIMIT);
    std::cout << "STARTING: Initiating particle simulation..."<<std::endl;
    sf::Clock clock;
    container::CircularContainer container;
    engine::PhysicsEngine physics_engine;
    generators::ParticleGenerator particle_generator;

    bool use_logging = false;
    particle_generator
      .setInitialPosition(this->windowCenter().x-350, this->windowCenter().y-280)
      .setMaxSize(20.0f)
      .setMinSize(5.0f)
      .setSpawnDelay(0.015f)
      .setTotalNumber(1000);
  
    container.setRadius(450.0f)
      .setPosition(this->windowCenter().x, this->windowCenter().y)
      .setColor(sf::Color::Black)
      .build();
    physics_engine
      .setFrameRate(constants::FRAME_LIMIT)
      .setSteps(1)
      .showLogging(use_logging)
      .build();

    while(this->window.isOpen()){
      while(const std::optional event = this->window.pollEvent()){
        if(event->is<sf::Event::Closed>()){
          std::cout << "EXITING: Closing particle simulation window..." <<std::endl;
          this->window.close();
        }
      }
      
      this->window.clear(sf::Color{33, 34, 43});
      this->draw(container);

      particle_generator.generateAsync(physics_engine.getTime(), physics_engine.getStepDeltaTime());
      
      for(auto &particle:particle_generator.getParticles())        
        this->draw(particle);
      
      physics_engine.updateTime();
      physics_engine.applyGravity(particle_generator.getParticles());
      physics_engine.applyCollision(particle_generator.getParticles());
      physics_engine.applyConstraint(container, particle_generator.getParticles());
      physics_engine.updatePosition(particle_generator.getParticles());
      this->window.display();
    }
  }

  // Private
  void App::draw(entities::Particle particle){
      sf::CircleShape circle;
      circle.setRadius(particle.getRadius());
      circle.setOrigin(particle.getOrigin());
      circle.setPosition(sf::Vector2f{particle.getPosition().x, particle.getPosition().y});
      circle.setFillColor(particle.getColor());
      this->window.draw(circle);
  }

  void App::draw(container::CircularContainer container){
      sf::CircleShape circle;
      circle.setRadius(container.getRadius());
      circle.setOrigin(container.getOrigin());
      circle.setPosition(sf::Vector2f{container.getPosition().x, container.getPosition().y});
      circle.setFillColor(container.getColor());
      this->window.draw(circle);
  }

  auto App::windowCenter()-> sf::Vector2f{return {this->window.getSize().x/2.0f, this->window.getSize().y/2.0f};}
}