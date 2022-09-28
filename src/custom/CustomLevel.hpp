#ifndef CUSTOM_LEVEL_HPP
#define CUSTOM_LEVEL_HPP

#include "../base/Level.hpp"

/**
 * Header for the custom level. Declares functions to be implemented. 
 */
class CustomLevel : public Level {
 public:
  CustomLevel();

  void initialize() override;

  void loadMap() override;

  void addObjectToLevel(float x, float y, char objectType);

  void revive() override;

  void nextLevel() override;

  void toggleRandomLevelMode() override;

  private:
  bool useRandomLevel;

};
#endif // CUSTOM_LEVEL_HPP