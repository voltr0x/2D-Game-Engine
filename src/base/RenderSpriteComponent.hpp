#ifndef BASE_RENDER_SPRITE_COMPONENT_HPP
#define BASE_RENDER_SPRITE_COMPONENT_HPP

#include <SDL.h>
#include <string>
#include "base/RenderComponent.hpp"

//! \brief Handles rendering a game object as a sprite.
class RenderSpriteComponent : public RenderComponent {
 public:
//   RenderSpriteComponent(GameObject& gameObject, const std::string assetName, int sw, int sh);
  RenderSpriteComponent(GameObject& gameObject, const std::string assetName, int tag);
  RenderSpriteComponent(GameObject& gameObject, int tag);

  virtual void render(SDL_Renderer* renderer) const override;

 private:
    const std::string mAssetName;
    // int w, h;
    int mTag{0};
};

#endif  // BASE_RENDER_SPRITE_COMPONENT_HPP