#include "SpriteGoalComponent.hpp"
#include "../Globals.hpp"
#include "../base/GameObject.hpp"

SpriteGoalComponent::SpriteGoalComponent(GameObject& gameObject)
    : RenderComponent(gameObject), 
    mSpriteNameDown{SETTINGS.spriteBasePath + "/objects/Mage/Death/death5.png"}, 
    mSpriteNameUp{SETTINGS.spriteBasePath + "/objects/Mage/Idle/idle11.png"} {
  gameObject.setDown(true);

}

void SpriteGoalComponent::render(SDL_Renderer* renderer) const {
  const GameObject& gameObject = getGameObject();
  // int mW = w > 0 ? w : int(gameObject.w());
  // int mH = h > 0 ? h : int(gameObject.h());
  int mW = int(gameObject.w());
  int mH = int(gameObject.h());
  int mX = int(gameObject.x());
  int mY = int(gameObject.y());

  if (gameObject.isDown()) {
    float angle = 0.0f;
    SDL_Point* center = NULL;
    SDL_RendererFlip flip = SDL_FLIP_NONE;

    SDL_Rect clip = {70, 70, 98, 98};
    SDL_Rect renderQuad = {mX, mY, mW, mH};
    SDL_RenderCopyEx(renderer, RESOURCE_MANAGER.getTexture(mSpriteNameDown), &clip, &renderQuad, angle, center, flip);

    // SDL_Rect drawRect = {mX, mY, mW, mH};
    // SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, 0x16);
    // SDL_RenderDrawRect(renderer, &drawRect);

    TTF_Font* mFont = RESOURCE_MANAGER.getFont("fonts/Junicode.ttf", 20);
    std::string mText = "Help...";
    // mText << level.points;
    TextTexture* mTextTexture = RESOURCE_MANAGER.getTextTexture(mFont, mText, {255, 255, 0, 255});
    mTextTexture->render(int(gameObject.x()), int(gameObject.y() - 10));
  } else {
    float angle = 0.0f;
    SDL_Point* center = NULL;
    SDL_RendererFlip flip = SDL_FLIP_NONE;

    SDL_Rect clip = {20, 50, 60, 60};
    SDL_Rect renderQuad = {mX, mY, mW, mH};
    SDL_RenderCopyEx(renderer, RESOURCE_MANAGER.getTexture(mSpriteNameUp), &clip, &renderQuad, angle, center, flip);

    // SDL_Rect drawRect = {mX, mY, mW, mH};
    // SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, 0x16);
    // SDL_RenderDrawRect(renderer, &drawRect);

    TTF_Font* mFont = RESOURCE_MANAGER.getFont("fonts/Junicode.ttf", 18);
    std::string mText = "lalalala...";
    // mText << level.points;
    TextTexture* mTextTexture = RESOURCE_MANAGER.getTextTexture(mFont, mText, {255, 255, 0, 255});
    mTextTexture->render(int(gameObject.x()) - 10, int(gameObject.y() - 20));
  }
}