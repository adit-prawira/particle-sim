#include "entities/particle.hpp"

namespace entities {
  // Public
  Particle& Particle::setRadius(float radius){
    this->radius = radius;
    return *this;
  }
  Particle& Particle::setColor(sf::Color color){
    this->color = color;
    return *this;
  }
  Particle& Particle::setInitialPosition(float x_position, float y_position){
    this->position = sf::Vector2f{x_position, y_position};
    this->previous_position = this->position;
    return *this;
  }

  Particle& Particle::setPosition(float x_position, float y_position){
    this->position = sf::Vector2f{x_position, y_position};
    return *this;
  }

  Particle& Particle::showLogging(bool show_logging){
    this->logger.showLogging(show_logging);
    return *this;
  }

  Particle& Particle::build(){
    std::vector<std::string> validation_messages;
    if(!this->radius) validation_messages.push_back("Radius of particle is required!");
    if(!validation_messages.empty()) throw std::runtime_error(this->compileValidations(validation_messages));
    return *this;
  }

  auto Particle::getRadius() -> float{return radius;}
  auto Particle::getOrigin() -> sf::Vector2f{return {radius, radius};}
  auto Particle::getColor() -> sf::Color {return color;}
  auto Particle::getPosition() -> sf::Vector2f{return position;}

  void Particle::updatePosition(float delta_time){
    const sf::Vector2f velocity = this->position - this->previous_position;
    
    this->logger.log(logger::Info, "Particle::updatePosition", "velocity", velocity);
    this->logger.log(logger::Info, "Particle::updatePosition", "acceleration", this->acceleration);    
    this->previous_position = this->position;

    this->logger.log(logger::Info, "Particle::updatePosition", "Previous particle position", this->previous_position);
    this->position = this->position + velocity + this->acceleration * (delta_time * delta_time);

    this->logger.log(logger::Info, "Particle::updatePosition", "Current particle position", this->position);
      
    this->acceleration = {};
    this->logger.log(logger::Info, "Particle::updatePosition", "Acceleration is resetted");  
  }

  void Particle::accelerate(float x_acceleration, float y_acceleration){
    this->acceleration += sf::Vector2f{x_acceleration, y_acceleration};
    this->logger.log(logger::Info, "Particle::accelerate", "Current acceleration", this->acceleration);
  }

  // Private
  std::string Particle::compileValidations(std::vector<std::string> validation_messages){
    std::ostringstream oss;
    for(size_t i = 0; i < validation_messages.size(); i++){
      oss << validation_messages[i];
      if(i != validation_messages.size() -1) oss << "\n";
    }
    return oss.str();
  }
}