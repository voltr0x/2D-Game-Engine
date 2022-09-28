#ifndef PLAT_FORMER_LEVEL_HPP
#define PLAT_FORMER_LEVEL_HPP

#include "../base/Level.hpp"

class PlatFormerLevel : public Level {
 public:
  PlatFormerLevel();

  void initialize() override;

  void loadMap() override;

  void addObjectToLevel(float x, float y, char objectType);

  void revive() override;
};
#endif  // PLAT_FORMER_LEVEL_HPP