#include "logger/logger.hpp"

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"

namespace logger {
  // Public

  void Logger::log(Level level, std::string name, std::string message, sf::Vector2f vector){
    std::cout << this->getColor(level) << this->getLevelLabel(level) << RESET << ": " << name << " => " << message << "\t" << "(x = " << vector.x << ", y = " << vector.y<<")" <<std::endl; 
  }

  void Logger::log(Level level, std::string name,std::string message){
    std::cout << this->getColor(level) << this->getLevelLabel(level) << RESET << ": " << name << " => " << message <<std::endl; 
  }

  // Private
  std::string Logger::getColor(Level level){
    switch (level) 
    {
    case Info:
      return GREEN;
    case Warn:
      return YELLOW;
    case Error:
      return RED;
    default:
      return RESET;
    }
  }
  std::string Logger::getLevelLabel(Level level){
    switch (level)
    {
    case Info:
      return "INFO";
    case Warn:
      return "WARN";
    case Error:
      return "ERROR";
    default:
      return "DEBUG";
    }
  }
}