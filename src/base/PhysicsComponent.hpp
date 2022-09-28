#ifndef BASE_PHYSICS_COMPONENT
#define BASE_PHYSICS_COMPONENT

#include "base/Component.hpp"
#include <box2d/box2d.h>

class Level;

//! \brief A component for handling simple physics. Has a velocity and
//! a solid property.  Solid objects prevent non-solid objects from
//! moving through them, and non-solid objects can collide with each
//! other.
class PhysicsComponent: public Component {
public:
  enum class Type {
    DYNAMIC_SOLID,
    STATIC_SOLID,
    STATIC_SENSOR
  };

  PhysicsComponent(GameObject & gameObject, Type type);
  PhysicsComponent(GameObject& gameObject, Type type, float density, float friction, float restitution);
  // TODO legacy constructor compatible with old Phyics, need to remove after box2d implemented
  PhysicsComponent(GameObject& gameObject, bool solid);

  virtual ~PhysicsComponent();

  void initBox2d(GameObject& gameObject);

  void setVx(float vx); //!< set x velocity
  void setVy(float vy); //!< set y velocity

  void addFx(float fx); //!< add force in x direction
  void addFy(float fy); //!< add force in y direction
  void addLinearForce(float fx, float fy); //!< add linear force(ApplyLinearImpulse)

  void postStep(); //!< Called after physics step.

private:

  b2Body *mBody;
  Type mType;
  float mDensity{0.0f}; //!< The density, usually in kg/m^2.
  float mFriction{0.0f}; //!< The friction coefficient, usually in the range [0,1].
  float mRestitution{0.0f}; //!<  The restitution (elasticity) usually in the range [0,1].
};

#endif
