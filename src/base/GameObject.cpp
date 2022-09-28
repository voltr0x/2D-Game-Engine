#include "base/GameObject.hpp"
#include <SDL.h>

GameObject::GameObject(Level& level, float x, float y, float w, float h, int tag)
    : mLevel(level),
      mX(x),
      mY(y),
      mW(w),
      mH(h),
      mInitX(x),
      mInitY(y),
      mTag(tag) {
}

GameObject::~GameObject() {
}

void GameObject::update(Level& level) {
  for (auto genericComponent : mGenericComponents) {
    genericComponent->update(level);
  }
}

void GameObject::collision(Level& level, std::shared_ptr<GameObject> obj) {
  for (auto genericComponent : mGenericComponents) {
    genericComponent->collision(level, obj);
  }
}

void GameObject::collision(std::shared_ptr<GameObject> obj) {
  for (auto genericComponent : mGenericComponents) {
    genericComponent->collision(mLevel, obj);
  }
}

void GameObject::postStep() {
  if (mPhysicsComponent) {
    mPhysicsComponent->postStep();
  }
}

void GameObject::animate() {
  if (mAnimationComponent) {
    mAnimationComponent->animate();
  }
}

void GameObject::render(SDL_Renderer* renderer) {
  if (mRenderComponent) {
    mRenderComponent->render(renderer);
  }
}

void GameObject::play(Level& level) {
  for (auto sfxComponent : mSfxComponents) {
    sfxComponent->play(level);
  }
}

void GameObject::display(Level& level, SDL_Renderer* renderer) {
  if (mDisplayComponent) {
    mDisplayComponent->display(level, renderer);
  }
}

bool GameObject::isColliding(const GameObject& obj) const {
  SDL_Rect thisRect = {int(x()), int(y()), int(w()), int(h())};
  SDL_Rect objRect = {int(obj.x()), int(obj.y()), int(obj.w()), int(obj.h())};
  SDL_Rect outRect;
  return SDL_IntersectRect(&thisRect, &objRect, &outRect);
}

bool GameObject::isColliding(float px, float py) const {
  SDL_Rect thisRect = {int(x()), int(y()), int(w()), int(h())};
  SDL_Point point = {int(px), int(py)};
  return SDL_PointInRect(&point, &thisRect);
}
