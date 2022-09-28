#ifndef SPRITE_GOAL_COMPONENT_HPP
#define SPRITE_GOAL_COMPONENT_HPP

#include <SDL.h>
#include <string>
#include "Globals.hpp"
#include "../base/RenderComponent.hpp"

//! \brief Handles rendering a game object as a sprite.
class SpriteGoalComponent : public RenderComponent {
 public:
  SpriteGoalComponent(GameObject& gameObject);

  virtual void render(SDL_Renderer* renderer) const override;

 private:
 const std::string mSpriteNameDown;
 const std::string mSpriteNameUp;
};

#endif  // SPRITE_GOAL_COMPONENT_HPP