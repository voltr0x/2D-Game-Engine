#include "base/Level.hpp"
#include <algorithm>
#include <iostream>
#include "../Globals.hpp"
#include "base/PhysicsManager.hpp"

Level::Level(int w, int h)
    : mW(w),
      mH(h) {
}

Level::~Level() {}

void Level::finalize() {
  mObjects.clear();
  mObjectsToAdd.clear();
  mObjectsToRemove.clear();
}

void Level::addObject(std::shared_ptr<GameObject> object) {
  mObjectsToAdd.push_back(object);
}

void Level::removeObject(std::shared_ptr<GameObject> object) {
  mObjectsToRemove.push_back(object);
}

bool Level::getCollisions(const GameObject& obj, std::vector<std::shared_ptr<GameObject>>& objects) const {
  objects.clear();
  for (auto gameObject : mObjects) {
    if (gameObject.get() != &obj && gameObject->isColliding(obj)) {
      objects.push_back(gameObject);
    }
  }

  return !objects.empty();
}

bool Level::getCollisions(float px, float py, std::vector<std::shared_ptr<GameObject>>& objects) const {
  objects.clear();
  for (auto gameObject : mObjects) {
    if (gameObject->isColliding(px, py)) {
      objects.push_back(gameObject);
    }
  }
  return !objects.empty();
}

void Level::updateEditor() {
  for (auto obj : mObjectsToAdd) {
    mObjects.push_back(obj);
  }
  mObjectsToAdd.clear();

  for (auto gameObject : mObjects) {
    gameObject->update(*this);
  }

  for (auto obj : mObjectsToRemove) {
    auto elem = std::find(mObjects.begin(), mObjects.end(), obj);
    if (elem != mObjects.end()) {
      mObjects.erase(elem);
    }
  }
  mObjectsToRemove.clear();
}

void Level::update() {
  bool pause = InputManager::getInstance().isKeyPressed(SDLK_p);
  if (pause) {
    SDL_Log("--> [PAUSE] handled in level::update()");
    if (mState == STATE_RUNING) {
      mState = STATE_PAUSE;
      return;
    } else if (mState == STATE_PAUSE) {
      mState = STATE_RUNING;
    }
  }

  for (auto obj : mObjectsToAdd) {
    mObjects.push_back(obj);
  }
  mObjectsToAdd.clear();

  for (auto gameObject : mObjects) {
    gameObject->update(*this);
  }
  
  if (!isGameOver()) {
    PhysicsManager::getInstance().step();
    for (auto gameObject : mObjects) {
      gameObject->postStep();
    }
    // TODO remove this
    // for (auto gameObject : mObjects) {
    //   gameObject->step(*this);
    // }
    for (auto gameObject : mObjects) {
      gameObject->animate();
    }
  }

  for (auto obj : mObjectsToRemove) {
    auto elem = std::find(mObjects.begin(), mObjects.end(), obj);
    if (elem != mObjects.end()) {
      mObjects.erase(elem);
    }
  }
  if (getLastInvincible() != -1 && getTimer() - getLastInvincible() >= 60 * 5) {
    setInvincible(-1);
  }
  bool mouseLeftClicked = INPUT_MANAGER.isMousePressed(SDL_BUTTON_LEFT);
      if (mouseLeftClicked) {
      std::vector<std::shared_ptr<GameObject>> objectsStore;
      int mMouseX, mMouseY;
        SDL_GetMouseState(&mMouseX, &mMouseY);
          int ShiftedX = mMouseX / SETTINGS.cellWidth * SETTINGS.cellWidth;
         int ShiftedY = mMouseY / SETTINGS.cellHeight * SETTINGS.cellHeight;
      getCollisions(ShiftedX, ShiftedY, objectsStore);
      for (std::shared_ptr<GameObject>& obj : objectsStore) {
        if (obj->tag() == TAG_ENEMY) {
          tagged = obj;
        }
      }
    }
  timer++;
  mObjectsToRemove.clear();
}

void Level::render(SDL_Renderer* renderer) {
  for (auto gameObject : mObjects) {
    if (getLastInvincible() != -1 && getTimer() % 2 == 1 && gameObject->tag() == TAG_PLAYER) {
      continue;
    }
    gameObject->render(renderer);
  }
}

void Level::play() {
  for (auto gameObject : mObjects) {
    gameObject->play(*this);
  }
}

void Level::display(SDL_Renderer* renderer) {
  for (auto gameObject : mObjects) {
    gameObject->display(*this, renderer);
  }
}

bool Level::isCollecting() {
  int res = mCollection - mLastScore;
  mLastScore = mCollection;
  return res;
}

void Level::reset() {
  setInvincible(-1);

  setState(STATE_START);
  mCollection = 0;
  setLives(SETTINGS.lives); // TODO may move out of Level class
  std::cout << "Reload map: " << std::endl;
  WORLD_MANAGER.loadCurrentLevel();
  loadMap();
}

void Level::nextLevel() {
  setInvincible(-1);

  setState(STATE_START);
  // mCollection = 0;
  std::cout << "next map: " << std::endl;
  WORLD_MANAGER.nextLevel();
  WORLD_MANAGER.loadCurrentLevel();
  loadMap();
}

bool Level::shouldPlayDeathSound() {
  if (mState == STATE_LOSE && !mPlayedDeathSound) {
    mPlayedDeathSound = true;
    return true;
  }
  return false;
}
