#include <SFML/Graphics.hpp>

namespace generators {
  class ColorGenerator {

    public:
      sf::Color generate(float value);
    private:  
      float green_coefficient = 0.33f;
      float blue_coefficient = 0.66f;
    };
}