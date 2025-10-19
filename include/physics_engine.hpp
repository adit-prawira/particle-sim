#pragma once
#include "particle.hpp"

namespace engine {
  class PhysicsEngine{
    // This is because 1 meter ~ 100 pixels
    // 9.81m/s^2 ~ 981 pixels/s^2
    static constexpr float GRAVITY = 981.0f;

    public:
      PhysicsEngine& setFrameRate(float frame_rate);
      PhysicsEngine& setSteps(uint32_t steps);
      PhysicsEngine& build();

      float getDeltaTime();
      float getTime();
      float getFrameRate();
      float getUpdateRate();

      void applyGravity(entities::Particle& particle);
      void updatePosition(entities::Particle& particle);
    private:
      uint32_t steps = 1;
      float time = 0.0f;
      float frame_rate = 0.0f;
      float delta_time = 0.0f;

  };
}