#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <sstream>

class Logger {
 private:
  /* data */

 public:
  Logger(/* args */);
  ~Logger();

  Logger& info();
  /**
   * Generic stream operator.
   */
  template <typename T>
  Logger& operator<<(T value) {
    std::cout << value;
    return *this;
  }

  /**
   * Overload of the stream operator to allow the use of std::endl.
   */
  Logger& operator<<(std::ostream& (*functionPointer)(std::ostream&)) {
    functionPointer(std::cout);
    // std::cout << "End line... " << std::endl;
    return *this;
  }
};


#endif