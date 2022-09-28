#if !defined(SFX_COMPONENT_HPP)
#define SFX_COMPONENT_HPP

#include "base/Component.hpp"
#include <memory>

class Level;

class SfxComponent : public Component {
 private:
  /* data */
 public:
  SfxComponent(GameObject& gameObject);

  virtual void play(Level& level);
};

#endif  // SFX_COMPONENT_HPP
