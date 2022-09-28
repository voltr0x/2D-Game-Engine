#include "RenderSpriteComponent.hpp"
#include "AnimationsComponent.hpp"
#include "GameObject.hpp"
#include "Globals.hpp"

// RenderSpriteComponent::RenderSpriteComponent(GameObject& gameObject, const std::string assetName, int sw, int sh)
//     : RenderComponent(gameObject),
//       mAssetName(assetName),
//       w(sw),
//       h(sh) {
// }
RenderSpriteComponent::RenderSpriteComponent(GameObject& gameObject, const std::string assetName, int tag)
    : RenderComponent(gameObject),
      mAssetName(assetName),
      mTag(tag) {
}

RenderSpriteComponent::RenderSpriteComponent(GameObject& gameObject, int tag)
    : RenderComponent(gameObject),
      mAssetName(""),
      mTag(tag) {
}
void RenderSpriteComponent::render(SDL_Renderer* renderer) const {
  const GameObject& gameObject = getGameObject();
  // int mW = w > 0 ? w : int(gameObject.w());
  // int mH = h > 0 ? h : int(gameObject.h());
  int mW = int(gameObject.w());
  int mH = int(gameObject.h());
  int mX = int(gameObject.x());
  int mY = int(gameObject.y());
  if (SETTINGS.showTopBar) {
    mY += SETTINGS.topBarHeight;
  }

  // std::cout << "mTag: " << mTag << " -> " << mAssetName << std::endl;
  float angle = 0.0f;
  SDL_Point* center = NULL;
  SDL_RendererFlip flip = SDL_FLIP_NONE;

  if (mTag == TAG_PLAYER || mTag == TAG_PLAYER_1) {
    // TODO add down sprite when be killed
    SDL_Rect clip = {20, 60, 50, 50};
    SDL_Rect renderQuad = {mX, mY, mW, mH};
    if (mTag == TAG_PLAYER_1) {
      clip = {25, 30, 75, 90};
      renderQuad = {mX, mY, 55, 55};
    }

    std::string path = gameObject.animationComponent()->getCurrent();
    flip = gameObject.isLeft() ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    SDL_RenderCopyEx(renderer, RESOURCE_MANAGER.getTexture(path), &clip, &renderQuad, angle, center, flip);
  } else if (mTag == TAG_COLLECTIBLE) {
    // SDL_Rect clip = {0, 0, 50, 50};
    std::string path = gameObject.animationComponent()->getCurrent();
    mW *= 0.5;
    mH *= 0.5;
    mX += mW * 0.5;
    mY += mH * 0.5;
    SDL_Rect renderQuad = {mX, mY, mW, mH};
    // TODO add more spirate like walk, jump
    // std::cout << "isLeft: " << gameObject.isLeft() << "isRight: " << gameObject.isRight() << std::endl;
    SDL_RenderCopyEx(renderer, RESOURCE_MANAGER.getTexture(path), NULL, &renderQuad, angle, center, flip);
  } else if (mTag == TAG_HEALTH) {
    // SDL_Rect clip = {0, 0, 50, 50};
    std::string path = gameObject.animationComponent()->getCurrent();
    mW *= 0.5;
    mH *= 0.5;
    mX += mW * 0.5;
    mY += mH * 0.5;
    SDL_Rect renderQuad = {mX, mY, mW, mH};
    // TODO add more spirate like walk, jump
    // std::cout << "isLeft: " << gameObject.isLeft() << "isRight: " << gameObject.isRight() << std::endl;
    SDL_RenderCopyEx(renderer, RESOURCE_MANAGER.getTexture(path), NULL, &renderQuad, angle, center, flip);
  } else if (mTag == TAG_COIN) {
    // SDL_Rect clip = {0, 0, 50, 50};
    std::string path = gameObject.animationComponent()->getCurrent();
    mW *= 0.5;
    mH *= 0.5;
    mX += mW * 0.5;
    mY += mH * 0.5;
    SDL_Rect renderQuad = {mX, mY, mW, mH};
    // TODO add more spirate like walk, jump
    // std::cout << "isLeft: " << gameObject.isLeft() << "isRight: " << gameObject.isRight() << std::endl;
    SDL_RenderCopyEx(renderer, RESOURCE_MANAGER.getTexture(path), NULL, &renderQuad, angle, center, flip);
  } else if (mTag == TAG_GOAL) {
    SDL_Rect clip = {70, 70, 98, 98};
    SDL_Rect renderQuad = {mX, mY, mW, mH};
    if (SETTINGS.gameType == "custom") {
      SDL_RenderCopyEx(renderer, RESOURCE_MANAGER.getTexture(mAssetName), NULL, &renderQuad, angle, center, flip);
    } else {
      SDL_RenderCopyEx(renderer, RESOURCE_MANAGER.getTexture(mAssetName), &clip, &renderQuad, angle, center, flip);
    }
  } else if (mTag == TAG_ENEMY) {
    SDL_Rect clip = {20, 60, 50, 50};
    SDL_Rect renderQuad = {mX, mY, mW, mH};
    // TODO add more spirate like walk, jump
    // std::cout << "isLeft: " << gameObject.isLeft() << "isRight: " << gameObject.isRight() << std::endl;
    std::string path = gameObject.animationComponent()->getCurrent();
    flip = gameObject.isLeft() ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    SDL_RenderCopyEx(renderer, RESOURCE_MANAGER.getTexture(path), &clip, &renderQuad, angle, center, flip);
  } else if (mTag == TAG_PASSIVE_ENEMY) {

    SDL_Rect clip = {5, 15, 400, 60};
    SDL_Rect renderQuad = {mX, mY, mW+400, mH};

    // TODO add more spirate like walk, jump
    // std::cout << "isLeft: " << gameObject.isLeft() << "isRight: " << gameObject.isRight() << std::endl;
    std::string path = gameObject.animationComponent()->getCurrent();
    flip = gameObject.isLeft() ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    SDL_RenderCopyEx(renderer, RESOURCE_MANAGER.getTexture(path), &clip, &renderQuad, angle, center, flip);
  } else if (mTag == TAG_TRIGGER_ZONE) {
    if (SETTINGS.debugMode) {
      const GameObject& gameObject = getGameObject();
      SDL_Rect fillRect = {int(gameObject.x()), int(gameObject.y()), int(gameObject.w()), int(gameObject.h())};
      SDL_SetRenderDrawColor(renderer, 200, 200, 200, 100);
      SDL_RenderFillRect(renderer, &fillRect);
    }
  } else if (mTag == TAG_POWERUP) {
    std::string path = gameObject.animationComponent()->getCurrent();
    mW *= 0.5;
    mH *= 0.5;
    mX += mW * 0.5;
    mY += mH * 0.5;
    SDL_Rect renderQuad = {mX, mY, mW, mH};
    // TODO add more spirate like walk, jump
    // std::cout << "isLeft: " << gameObject.isLeft() << "isRight: " << gameObject.isRight() << std::endl;
    SDL_RenderCopyEx(renderer, RESOURCE_MANAGER.getTexture(path), NULL, &renderQuad, angle, center, flip);
  }
  if (SETTINGS.debugMode) {
    SDL_Rect drawRect = {mX, mY, mW, mH};
    SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, 0x99);
    SDL_RenderDrawRect(renderer, &drawRect);
  }
  //   TTF_Font* mFont = RESOURCE_MANAGER.getFont("fonts/Junicode.ttf", 28);
  //   std::string mText = "++";
  //   // mText << level.points;
  //   TextTexture* mTextTexture = RESOURCE_MANAGER.getTextTexture(mFont, mText, {0, 0, 0, 255});
  //   mTextTexture->render(int(gameObject.x()), int(gameObject.y() - 10));
}