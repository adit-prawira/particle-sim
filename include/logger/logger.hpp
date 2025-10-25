#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>

namespace logger {
  enum Level {
    Info,
    Warn,
    Error
  };

  class Logger{
    public:
      Logger& showLogging(float show_logging);
      void log(Level level, std::string name, std::string message, sf::Vector2f vector);
      void log(Level level, std::string name, std::string message);
    private:
      bool show_logging = false;
      std::string getColor(Level level);
      std::string getLevelLabel(Level level);
  };
}