#ifndef BASE_RENDER_BLOCK_COMPONENT_HPP
#define BASE_RENDER_BLOCK_COMPONENT_HPP

#include <SDL.h>
#include <string>
#include "base/RenderComponent.hpp"

//! \brief Handles rendering a game object as a sprite.
class RenderBlockComponent : public RenderComponent {
 public:
  RenderBlockComponent(GameObject& gameObject, const std::string assetName);

  virtual void render(SDL_Renderer* renderer) const override;

 private:
    const std::string mAssetName;
};

#endif  // BASE_RENDER_BLOCK_COMPONENT_HPP