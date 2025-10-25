#include <vector>

#include <entities/particle.hpp>
#include <generators/color_generator.hpp>
#include <random>

namespace generators {
  class ParticleGenerator {
    public:
      ParticleGenerator& setSpawnDelay(float time);
      ParticleGenerator& setSpawnSpeed(float speed);
      ParticleGenerator& setTotalNumber(int total);
      ParticleGenerator& setMinSize(float size);
      ParticleGenerator& setMaxSize(float size);
      ParticleGenerator& setInitialPosition(float x, float y);

      std::vector<entities::Particle>& getParticles();

      void generateAsync(float frame_time, float step_delta_time);
    
    private:
      float spawn_speed = 1200.0f;
      float spawn_delay = 0.025f;
      int total_particles = 10;
      int max_angle = 1.0f;
      float max_size = 40;
      float min_size = 10;

      std::vector<entities::Particle> particles;
      sf::Clock clock;
      sf::Vector2f initial_position;
      
      float generateRadius();
  };
}