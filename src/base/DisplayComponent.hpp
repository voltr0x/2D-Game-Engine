#if !defined(BASE_DISPLAY_COMPONENT_HPP)
#define BASE_DISPLAY_COMPONENT_HPP

#include <SDL.h>
#include "base/Component.hpp"

class Level;

class DisplayComponent : public Component {
 private:
  /* data */
 public:
  DisplayComponent(GameObject& gameObject);

  virtual void display(Level& level, SDL_Renderer* renderer);  //!< display infor.
};

#endif  // BASE_DISPLAY_COMPONENT_HPP
