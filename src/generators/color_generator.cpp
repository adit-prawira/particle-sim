#include "generators/color_generator.hpp"

namespace generators {
  sf::Color ColorGenerator::generate(float value){
    const float r = sin(value);
    const float g = sin(value + this->green_coefficient * 2 * M_PI);
    const float b = sin(value + this->blue_coefficient*2*M_PI);
    return {
      static_cast<uint8_t>(250 * r * r),
      static_cast<uint8_t>(250 * g * g),
      static_cast<uint8_t>(250 * b * b)
    };
  }
}