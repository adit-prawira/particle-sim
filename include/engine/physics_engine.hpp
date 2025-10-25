#pragma once
#include "logger/logger.hpp"
#include "entities/particle.hpp"
#include "container/circular_container.hpp"

namespace engine {
  class PhysicsEngine{
    // This is because 1 meter ~ 100 pixels
    // 9.81m/s^2 ~ 981 pixels/s^2
    static constexpr float GRAVITY = 981.0f;

    public:
      PhysicsEngine& setFrameRate(float frame_rate);
      PhysicsEngine& setSteps(uint32_t steps);
      PhysicsEngine& setCollisionResponseCoefficient(float response_coefficient);
      PhysicsEngine& showLogging(bool show_logging);
      PhysicsEngine& build();

      float getDeltaTime();
      float getTime();
      float getFrameRate();
      float getUpdateRate();

      void applyGravity(std::vector<entities::Particle> &particles);
      void updatePosition(std::vector<entities::Particle> &particles);
      void applyConstraint(container::CircularContainer circularContainer, std::vector<entities::Particle> &particles);
      void applyCollision(std::vector<entities::Particle> &particles);
    private:
      uint32_t steps = 1;
      float time = 0.0f;
      float frame_rate = 0.0f;
      float delta_time = 0.0f;
      float response_coefficient = 0.75f;
      logger::Logger logger;

  };
}