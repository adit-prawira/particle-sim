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
    std::vector<entities::Particle> particles;
    engine::PhysicsEngine physics_engine;

    container.setRadius(450.0f)
      .setPosition(this->windowCenter().x, this->windowCenter().y)
      .setColor(sf::Color::Black)
      .build();
    physics_engine
      .setFrameRate(constants::FRAME_LIMIT)
      .setSteps(1)
      .showLogging(true)
      .build();

    while(this->window.isOpen()){
      while(const std::optional event = this->window.pollEvent()){
        if(event->is<sf::Event::Closed>()){
          std::cout << "EXITING: Closing particle simulation window..." <<std::endl;
          this->window.close();
        }
      }
      this->window.clear(sf::Color{61, 69, 63});
      this->draw(container);

      if(particles.size() < 10 && clock.getElapsedTime().asSeconds() >= 1.0f){
        clock.restart();
        particles.push_back(
          entities::Particle()
            .setRadius(40.0f)
            .setInitialPosition(this->windowCenter().x+300, this->windowCenter().y)
            .setColor(sf::Color::White)
            .showLogging(false)
            .build()
        );
      }

      for(auto &particle:particles)        
        this->draw(particle);
        
      physics_engine.applyGravity(particles);
      physics_engine.applyCollision(particles);
      physics_engine.applyConstraint(container, particles);
      physics_engine.updatePosition(particles);
      this->window.display();
    }
  }

  // Private
  void App::draw(entities::Particle particle){
      sf::CircleShape circle;
      circle.setRadius(particle.getRadius());
      circle.setOrigin(particle.getOrigin());
      circle.setPosition(sf::Vector2f{particle.getPosition().x, particle.getPosition().y});
      circle.setFillColor(sf::Color::White);
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