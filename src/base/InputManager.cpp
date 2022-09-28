#include "InputManager.hpp"
#include <algorithm>

InputManager&
InputManager::getInstance() {
  static InputManager* instance = new InputManager();
  return *instance;
}

void InputManager::startUp() {
}

void InputManager::shutDown() {
}

void InputManager::resetForFrame() {
  mKeysPressed.clear();
  mMousePressed.clear();
}

void InputManager::handleEvent(const SDL_Event& e) {
  if (e.type == SDL_KEYDOWN) {
    auto elem = mKeysDown.find(e.key.keysym.sym);
    if (elem == mKeysDown.end()) {
      mKeysPressed.insert(e.key.keysym.sym);
    }
    mKeysDown.insert(e.key.keysym.sym);
  } else if (e.type == SDL_KEYUP) {
    mKeysDown.erase(e.key.keysym.sym);
  } else if (e.type == SDL_MOUSEBUTTONDOWN) {
    auto elem = mMouseDown.find(e.button.button);
    if (elem == mMouseDown.end()) {
      mMousePressed.insert(e.button.button);
    }
    mMouseDown.insert(e.button.button);
  } else if (e.type == SDL_MOUSEBUTTONUP) {
    mMouseDown.erase(e.button.button);
  }
}

bool InputManager::isKeyDown(SDL_Keycode k) const {
  return mKeysDown.find(k) != mKeysDown.end();
}

bool InputManager::isKeyPressed(SDL_Keycode k) const {
  return mKeysPressed.find(k) != mKeysPressed.end();
}

bool InputManager::isMouseDown(Uint8 k) const {
  return mMouseDown.find(k) != mMouseDown.end();
}

bool InputManager::isMousePressed(Uint8 k) const {
  return mMousePressed.find(k) != mMousePressed.end();
}
