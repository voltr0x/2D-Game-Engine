#include "base/RectRenderComponent.hpp"
#include "base/GameObject.hpp"
#include "ResourceManager.hpp"
#include <iostream>

RectRenderComponent::RectRenderComponent(GameObject & gameObject, const std::string& assetName):
  RenderComponent(gameObject),
  m_assetName(assetName)
{
}

void
RectRenderComponent::render(SDL_Renderer * renderer) const
{
  const GameObject & gameObject = getGameObject();
  SDL_Rect fillRect = { int(gameObject.x()), int(gameObject.y()), int(gameObject.w()), int(gameObject.h()) };
  SDL_RenderCopy(renderer, ResourceManager::getInstance().getTexture(m_assetName), NULL, &fillRect);
}
