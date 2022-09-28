#ifndef BASE_RECT_RENDER_COMPONENT
#define BASE_RECT_RENDER_COMPONENT

#include "base/RenderComponent.hpp"
#include <SDL.h>
#include <string> 

//! \brief Handles rendering a game object as a simple rectangle.
class RectRenderComponent: public RenderComponent {
public:

  RectRenderComponent(GameObject & gameObject, const std::string& assetName);
  
  virtual void render(SDL_Renderer * renderer) const override;

private:
  const std::string& m_assetName;

};

#endif
