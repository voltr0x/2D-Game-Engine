#ifndef CUSTOM_RANDOM_GENERATOR_HPP
#define CUSTOM_RANDOM_GENERATOR_HPP

#include <vector>
#include <string>

/**
 * @brief Class to randomly generate a level for custom
 * 
 */
class CustomRandomLevelGenerator  {
public:
    static std::vector<std::vector<std::string>> generateLevel(int rows, int cols, uint64_t seed);
};



#endif