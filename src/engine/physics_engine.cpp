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

  auto PhysicsEngine::build() -> PhysicsEngine& {return *this;}

  auto PhysicsEngine::getDeltaTime() -> float{return getUpdateRate()/static_cast<float>(steps);}
  auto PhysicsEngine::getTime() -> float{return time;}
  auto PhysicsEngine::getUpdateRate() -> float{return 1.0/static_cast<float>(this->frame_rate);}

  void PhysicsEngine::applyGravity(entities::Particle& particle){
    particle.accelerate(0.0f, GRAVITY);
  }

  void PhysicsEngine::updatePosition(entities::Particle& particle){
    particle.updatePosition(this->getDeltaTime());
  }
}