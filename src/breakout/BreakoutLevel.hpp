#ifndef BREAKOUT_LEVEL
#define BREAKOUT_LEVEL

#include "../base/Level.hpp"

class BreakoutLevel : public Level {
 public:
  BreakoutLevel();

  void initialize() override;

  void loadMap() override;

  void revive() override;

};
#endif