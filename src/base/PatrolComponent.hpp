#ifndef BASE_PATROL_COMPONENT
#define BASE_PATROL_COMPONENT

#include "base/GenericComponent.hpp"
#include <utility>
#include <vector>

//! \brief A component that causes its game object to patrol back and forth.
class PatrolComponent: public GenericComponent {
public:

  PatrolComponent(GameObject & gameObject, std::vector<std::pair<float,float>> locs, float speed);
  
  virtual void update(Level & level);

private:

  // TODO: add variables
  float speed_;
  int index;
  int count;
  std::vector<std::pair<float,float>> m_locs;
  
};

#endif
