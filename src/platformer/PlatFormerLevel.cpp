#include "PlatFormerLevel.hpp"
#include "../Enemy.hpp"
#include "../MapCell.hpp"
#include "../MapObjects.hpp"
#include "../Player.hpp"
#include "../TopBar.hpp"

PlatFormerLevel::PlatFormerLevel()
    : Level(SETTINGS.screenWidth, SETTINGS.screenHeight) {
}

void PlatFormerLevel::initialize() {
  setTitle(SETTINGS.appName);
  setLives(SETTINGS.lives);
  addObject(std::make_shared<MapGrid>(*this, SETTINGS.cellWidth, SETTINGS.cellHeight));
  // loadMap();
  loadMap();

  addObject(std::make_shared<Displayer>(*this));
  addObject(std::make_shared<SoundEffects>(*this, BGM));
}

void PlatFormerLevel::loadMap() {
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

      addObjectToLevel(x, y, col[jj][0]);
    }

    // delete spawner; TODO: deleting thsi doesn't work, fix later
    //  std::cout << std::endl;
    //  level->addObject(std::make_shared<MapCell>(ii * sizeY, 9 * sizeX));
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
  addObject(std::make_shared<DeathBox>(*this, BORDER_BOX[POS_BOTTOM]));

  if (SETTINGS.showTopBar) {
    addObject(std::make_shared<TopBar>(*this));
    addObject(std::make_shared<TopBarButton>(*this, 15, 5, TAG_TB_LAUNCH));
    addObject(std::make_shared<TopBarButton>(*this, 130, 5, TAG_TB_PLATFORMER_EDITOR));
  }
};

void PlatFormerLevel::addObjectToLevel(float x, float y, char objectType) {
  if (std::isdigit(objectType) == 0) {
    if (objectType == 'X') {
      addObject(std::make_shared<MapCell>(*this, x, y, 2));
    } else if (objectType == 'P') {
      addObject(std::make_shared<Player>(*this, x, y));
    } else if (objectType == 'G') {
      addObject(std::make_shared<Goal>(*this, x, y));
    } else if (objectType == 'C') {
      std::string collectiblePath = SETTINGS.spriteBasePath + "/collectibles/coins/Gold";
      addObject(std::make_shared<Collectible>(*this, x, y, collectiblePath, "Gold"));
    } else if (objectType == 'I') {
      std::string powerupPath = SETTINGS.spriteBasePath + "/collectibles/coins/Silver";
      addObject(std::make_shared<Powerup>(*this, x, y, powerupPath, "Silver"));
    } else if (objectType == 'E') {
      addObject(std::make_shared<Enemy>(*this, x, y));
    }
  } else {
    addObject(std::make_shared<MapCell>(*this, x, y, objectType - '0'));
  }
}

void PlatFormerLevel::revive() {
  setInvincible(-1);
  setState(STATE_RUNING);
  //
  for (auto gameObject : mObjects) {
    // TODO refactor to resetables
    if (gameObject->tag() == TAG_PLAYER) {
      float initX = gameObject->initX();
      float initY = gameObject->initY();
      removeObject(gameObject);
      if (gameObject->tag() == TAG_PLAYER) {
        addObject(std::make_shared<Player>(*this, initX, initY));
      }
    }
  }
  SDL_Log("revived [state: %d]", state());
}
