#include "generators/particle_generator.hpp"

namespace generators{
  ParticleGenerator& ParticleGenerator::setSpawnDelay(float time){
    this->spawn_delay = time;
    return *this;
  }
  
  ParticleGenerator& ParticleGenerator::setSpawnSpeed(float speed){
    this->spawn_speed = speed;
    return *this;
  }
  ParticleGenerator& ParticleGenerator::setTotalNumber(int total){
    this->total_particles = total;
    return *this;
  }

  ParticleGenerator& ParticleGenerator::setMinSize(float size){
    this->min_size = size;
    return *this;
  }

  ParticleGenerator& ParticleGenerator::setMaxSize(float size){
    this->max_size = size;
    return *this;
  }

  ParticleGenerator& ParticleGenerator::setInitialPosition(float x, float y){
    this->initial_position = sf::Vector2f{x,y};
    return *this;
  }

  auto ParticleGenerator::getParticles() -> std::vector<entities::Particle>&{return particles;}

  void ParticleGenerator::generateAsync(float frame_time, float step_delta_time){
    if(particles.size() < this->total_particles && clock.getElapsedTime().asSeconds() >= this->spawn_delay){
      clock.restart();
      const float angle = this->max_angle * sin(step_delta_time) * M_PI *0.5f;

      std::cout << "RADIUS -> " << this->generateRadius() << std::endl;
      particles.push_back(
        entities::Particle()
          .setRadius(this->generateRadius())
          .setInitialPosition(this->initial_position.x, this->initial_position.y)
          .setColor(generators::ColorGenerator().generate(frame_time))
          .showLogging(false)
          .build()
      );
    }
  }

  // Private
  float ParticleGenerator::generateRadius(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distr(this->min_size, this->max_size);
    return distr(gen);
  }
}