#include "Logger.hpp"

Logger::Logger(/* args */) {
}

Logger::~Logger() {
}

Logger& Logger::info() {
  std::cout << ">> LOG << ";
  return *this;
}
