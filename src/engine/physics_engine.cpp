#include "engine/physics_engine.hpp"

namespace engine{
  PhysicsEngine& PhysicsEngine::setFrameRate(float frame_rate){
    this->frame_rate = frame_rate;
    return *this;
  }

  PhysicsEngine& PhysicsEngine::setSteps(uint32_t steps){
    this->steps = steps;
    return *this;
  }

  PhysicsEngine& PhysicsEngine::showLogging(bool show_logging){
    this->logger.showLogging(show_logging);
    return *this;
  }

  auto PhysicsEngine::build() -> PhysicsEngine& {return *this;}

  auto PhysicsEngine::getDeltaTime() -> float{return getUpdateRate()/static_cast<float>(steps);}
  auto PhysicsEngine::getTime() -> float{return time;}
  auto PhysicsEngine::getUpdateRate() -> float{return 1.0/static_cast<float>(this->frame_rate);}
  
  void PhysicsEngine::applyGravity(std::vector<entities::Particle> &particles){
    for(auto &particle : particles)
      particle.accelerate(0.0f, GRAVITY);
  }

  void PhysicsEngine::updatePosition(std::vector<entities::Particle> &particles){
    for(auto &particle: particles)
      particle.updatePosition(this->getDeltaTime());
  }

  void PhysicsEngine::applyConstraint(container::CircularContainer container, std::vector<entities::Particle> &particles){
    for(auto &particle:particles){
      const sf::Vector2f position_vector_diff = particle.getPosition() - container.getPosition();
      const float distance = std::sqrt(position_vector_diff.x*position_vector_diff.x + position_vector_diff.y*position_vector_diff.y);
      if(distance > container.getRadius() - particle.getRadius()){
        const sf::Vector2f normalized = position_vector_diff/distance;
        const sf::Vector2f newPosition = container.getPosition() + normalized * (container.getRadius() - particle.getRadius());
        particle.setPosition(newPosition.x, newPosition.y);
      }
    }
  }

  void PhysicsEngine::applyCollision(std::vector<entities::Particle> &particles){
    const uint64_t total_particles = particles.size();
    // iterate each particle
    for(auto i = 0; i < total_particles; ++i){
      entities::Particle& current_particle = particles[i];

      // compare current particle with the rest of the objects
      for(auto j = i+1; j < total_particles; ++j){

        entities::Particle& neighbour_particle = particles[j];
        const sf::Vector2f position_vector_diff = current_particle.getPosition() - neighbour_particle.getPosition();
        const float distance = std::sqrt(position_vector_diff.x*position_vector_diff.x + position_vector_diff.y*position_vector_diff.y);
        const float minimum_distance = current_particle.getRadius() + neighbour_particle.getRadius();

        if(distance*distance < minimum_distance*minimum_distance){
          const sf::Vector2f normalized_vector = position_vector_diff/distance;
          const float current_particle_mass_ratio = current_particle.getRadius() / (current_particle.getRadius() + neighbour_particle.getRadius());
          const float neighbour_particle_mass_ratio = neighbour_particle.getRadius() / (neighbour_particle.getRadius() + current_particle.getRadius());
          const float delta = 0.5*this->response_coefficient*(distance - minimum_distance);
          
          const sf::Vector2f updated_current_particle_position = current_particle.getPosition() - normalized_vector*(neighbour_particle_mass_ratio*delta);
          const sf::Vector2f updated_neighbour_particle_position = neighbour_particle.getPosition() + normalized_vector*(current_particle_mass_ratio*delta);
          
          this->logger.log(logger::Info, "PhysicsEngine::applyCollision", "CURRENT PARTICLE: Updated position", updated_current_particle_position);
          this->logger.log(logger::Info, "PhysicsEngine::applyCollision", "NEIGHBOUR PARTICLE: Updated position", updated_current_particle_position);

          current_particle.setPosition(updated_current_particle_position.x, updated_current_particle_position.y);
          neighbour_particle.setPosition(updated_neighbour_particle_position.x, updated_neighbour_particle_position.y);

          this->logger.log(logger::Info, "PhysicsEngine::applyCollision", "ACTUAL CURRENT PARTICLE: Updated position", current_particle.getPosition());
          this->logger.log(logger::Info, "PhysicsEngine::applyCollision", "ACTUAL NEIGHBOUR PARTICLE: Updated position", neighbour_particle.getPosition());
        }
      }
    }

  }
}