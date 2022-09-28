#include "BreakoutLevel.hpp"
#include "../TopBar.hpp"
#include "BreakoutObjects.hpp"
#include "MapCell.hpp"
#include "MapObjects.hpp"

BreakoutLevel::BreakoutLevel()
    : Level(SETTINGS.screenWidth, SETTINGS.screenHeight) {
}

void BreakoutLevel::initialize() {
  setTitle(SETTINGS.appName);
  setLives(SETTINGS.lives);
  addObject(std::make_shared<MapGrid>(*this, SETTINGS.cellWidth, SETTINGS.cellHeight));

  loadMap();

  addObject(std::make_shared<Displayer>(*this));
  addObject(std::make_shared<SoundEffects>(*this, BGM));
}

void BreakoutLevel::loadMap() {
  mSaved = false;
  mLevelName = WORLD_MANAGER.getLevelName();
  mLevelId = WORLD_MANAGER.getLevel();

  // empty objects;
  std::cout << "Level: " << mLevelId << "; Total objects: " << mObjects.size() << std::endl;
  for (auto gameObject : mObjects) {
    if (gameObject->tag() > TAG_IGNORE && gameObject->tag() < TAG_EDITOR_EMPTY) {
      mObjectsToRemove.push_back(gameObject);
    }
  }

  // BaseSpawner* spawner = SpawnerFactory::getSpawner(SETTINGS.gameType);
  // spawner->loadLevel(*this);

  std::vector<std::vector<std::string>> mMapVector = WORLD_MANAGER.mapVector();
  int sizeY = SETTINGS.cellHeight;
  int sizeX = SETTINGS.cellWidth;

  for (size_t ii = 0; ii < mMapVector.size(); ++ii) {
    // col
    std::vector<std::string> col = mMapVector[ii];
    // std::cout << col.size() << std::endl;
    for (size_t jj = 0; jj < col.size(); ++jj) {
      // std::cout << col[jj][0] << " ";
      float x = jj * sizeX;
      float y = ii * sizeY;
      char objectType = col[jj][0];

      if (isdigit(objectType) && objectType != '0') {
        addObject(std::make_shared<BreakoutBrick>(*this, objectType - '0', x, y));
      } else if (objectType == 'P') {
        addObject(std::make_shared<BreakoutPaddle>(*this, x, y));
      } else if (objectType == 'B') {
        addObject(std::make_shared<BreakoutBall>(*this, x, y));
      }
    }
  }
  // TODO need refactor to a struct/class or out of the Level
  static std::vector<std::vector<int>> BORDER_BOX = {
      {0, 0 - BORDER_SIZE, SETTINGS.screenWidth, BORDER_SIZE},        // top
      {SETTINGS.screenWidth, 0, BORDER_SIZE, SETTINGS.screenHeight},  // right
      {0, SETTINGS.screenHeight, SETTINGS.screenWidth, BORDER_SIZE},  // bottom
      {0 - BORDER_SIZE, 0, BORDER_SIZE, SETTINGS.screenHeight}};      // left

  addObject(std::make_shared<BorderBox>(*this, BORDER_BOX[POS_TOP], TAG_BORDER_TOP));
  addObject(std::make_shared<BorderBox>(*this, BORDER_BOX[POS_LEFT], TAG_BORDER_LEFT));
  addObject(std::make_shared<BorderBox>(*this, BORDER_BOX[POS_RIGHT], TAG_BORDER_RIGHT));
  // addObject(std::make_shared<BorderBox>(*this, BORDER_BOX[POS_BOTTOM], TAG_BORDER_BOTTOM));

  std::vector<int> deathBoxBottom = {0, SETTINGS.screenHeight - BORDER_SIZE, SETTINGS.screenWidth, BORDER_SIZE};
  addObject(std::make_shared<DeadZone>(*this, deathBoxBottom));

  if (SETTINGS.showTopBar) {
    addObject(std::make_shared<TopBar>(*this));
    addObject(std::make_shared<TopBarButton>(*this, 15, 5, TAG_TB_LAUNCH));
    addObject(std::make_shared<TopBarButton>(*this, 130, 5, TAG_TB_BREAKOUT_EDITOR));
  }
}

void BreakoutLevel::revive() {
  setInvincible(-1);
  setState(STATE_RUNING);
  //
  for (auto gameObject : mObjects) {
    // TODO refactor to resetables
    if (gameObject->tag() == TAG_PLAYER || gameObject->tag() == TAG_BALL) {
      float initX = gameObject->initX();
      float initY = gameObject->initY();
      removeObject(gameObject);
      if (gameObject->tag() == TAG_PLAYER) {
        addObject(std::make_shared<BreakoutPaddle>(*this, initX, initY));
      }
      if (gameObject->tag() == TAG_BALL) {
        addObject(std::make_shared<BreakoutBall>(*this, initX, initY));
      }
    }
  }
  SDL_Log("revived [state: %d]", state());
}