#include "RenderBlockComponent.hpp"
#include "GameObject.hpp"
#include "Globals.hpp"

RenderBlockComponent::RenderBlockComponent(GameObject& gameObject, const std::string assetName)
    : RenderComponent(gameObject),
      mAssetName(assetName) {
}

void RenderBlockComponent::render(SDL_Renderer* renderer) const {
  const GameObject& gameObject = getGameObject();
  int mY = int(gameObject.y());
  if (SETTINGS.showTopBar) {
    mY += SETTINGS.topBarHeight;
  }

  SDL_Rect fillRect = {int(gameObject.x()), mY, int(gameObject.w()), int(gameObject.h())};
  SDL_RenderCopy(renderer, RESOURCE_MANAGER.getTexture(mAssetName), NULL, &fillRect);

  //   SDL_Rect drawRect = {int(gameObject.x()), int(gameObject.y()), mW, mH};
  //   SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, 0xFF);
  //   SDL_RenderDrawRect(renderer, &drawRect);
}