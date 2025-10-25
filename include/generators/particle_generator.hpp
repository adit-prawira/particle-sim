#include <vector>

#include <entities/particle.hpp>

namespace generators {
  class ParticleGenerator {
    public:
      ParticleGenerator& setInitialParticles(std::vector<entities::Particle>& particles);
      ParticleGenerator& setTotalNumber(int total);
      ParticleGenerator& setMinSize(float size);
      ParticleGenerator& setMaxSize(float size);

      void generateAsync(float delay);
      void generate();
  };
}