#if !defined(BREAKOUT_INPUT_COMPONENT_HPP)
#define BREAKOUT_INPUT_COMPONENT_HPP

#include "base/GenericComponent.hpp"
#include "base/Level.hpp"

/**
 * @brief A component for handling keyboard inputs.
 *
 */
class BreakoutInputComponent : public GenericComponent {
 public:
  BreakoutInputComponent(GameObject& gameObject, float speed, float jump, float gravity);

  virtual void update(Level& level) override;

 private:
  float mSpeed;
  float mJump;
  float mGravity;
  int mCount;
};

#endif // BREAKOUT_INPUT_COMPONENT_HPP
