#ifndef BASE_ANIMATIONS_COMPONENT
#define BASE_ANIMATIONS_COMPONENT

#include "base/Component.hpp"
#include <memory>
#include <string>
#include <utility>
#include <vector>

class Level;

//! \brief A component for handling simple physics. Has a velocity and
//! a solid property.  Solid objects prevent non-solid objects from
//! moving through them, and non-solid objects can collide with each
//! other.
class AnimationsComponent: public Component {
public:
  AnimationsComponent(GameObject& GameObject);
  virtual void animate() = 0;
  virtual std::string getCurrent() = 0;
  virtual int getCount() = 0;
};

class StaticAnimationsComponent: public AnimationsComponent {
public:
  StaticAnimationsComponent(GameObject & gameObject, std::string basePath, std::string prefix, int max);
  void animate() override;
  std::string getCurrent() override;
  int getCount() override {return count;}
private:
  std::string basePath_;
  std::string prefix_;
  int count{-1};
  int max_;
};

class DynamicAnimationsComponent: public AnimationsComponent {
public:
  DynamicAnimationsComponent(GameObject & gameObject, std::string basePath, std::vector<std::pair<std::string,int>> prefixes);
  void animate() override;
  std::string getCurrent() override;
  int getCount() override {return count;}
private:
  // NOTE: must be in order. Idle, Walk, Jump
  std::string basePath_;
  std::vector<std::pair<std::string,int>> prefixes_;
  int count{-1};
};
#endif