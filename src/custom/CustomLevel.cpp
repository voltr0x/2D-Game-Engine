#include "CustomLevel.hpp"
#include <chrono>
#include "../MapCell.hpp"
#include "../MapObjects.hpp"
#include "../TopBar.hpp"
#include "CustomObjects.hpp"
#include "CustomRandomGenerator.hpp"
#include "UIBox.hpp"

/**
 * Gets the wide and height of the level screen.
 */
CustomLevel::CustomLevel()
    : Level(SETTINGS.screenWidth, SETTINGS.screenHeight), useRandomLevel{false} {
}

/**
 * Creates the level. Gets the lives and name of the window. Adds the map grid and puts the objects into the grid.
 * Gets the sound effects and display method.
 */
void CustomLevel::initialize() {
  setTitle(SETTINGS.appName);
  setLives(SETTINGS.lives);
  addObject(std::make_shared<MapGrid>(*this, SETTINGS.cellWidth, SETTINGS.cellHeight));
  // loadMap();
  loadMap();

  addObject(std::make_shared<Displayer>(*this));
  addObject(std::make_shared<SoundEffects>(*this, BGM));
}

/**
 * Indetifies the current level and loades the game objects for it.
 */
void CustomLevel::loadMap() {
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

  for (size_t ii = 0; ii < mMapVector.size(); ++ii) {
    // col
    std::vector<std::string> col = mMapVector[ii];
    // std::cout << col.size() << std::endl;
    for (size_t jj = 0; jj < col.size(); ++jj) {
      // std::cout << col[jj][0] << " ";
      float x = SETTINGS.getFixedColX(jj);
      // float y = SETTINGS.getFixedRowY(ii);
      // float x = jj * SETTINGS.cellWidth;
      float y = ii * SETTINGS.cellHeight;

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
  addObject(std::make_shared<BorderBox>(*this, BORDER_BOX[POS_BOTTOM], TAG_BORDER_BOTTOM));
  addObject(std::make_shared<UIBox>(*this, TAG_PLAYER_UI_BOX));
  // addObject(std::make_shared<UIBox>(*this, TAG_PLAYER_ENEMEY_BOX));

  if (SETTINGS.showTopBar) {
    addObject(std::make_shared<TopBar>(*this));
    addObject(std::make_shared<TopBarButton>(*this, 15, 5, TAG_TB_LAUNCH));
    addObject(std::make_shared<TopBarButton>(*this, 130, 5, TAG_TB_CUSTOM_EDITOR));
  }
};

/**
 * Adds a specific object to the level based on the object type.
 */
void CustomLevel::addObjectToLevel(float x, float y, char objectType) {
  if (std::isdigit(objectType) == 0) {
    if (objectType == 'X') {
      addObject(std::make_shared<MapCell>(*this, x, y, 1));
    } else if (objectType == 'D') {
      addObject(std::make_shared<CustomDoor>(*this, x, y));
    } else if (objectType == 'P') {
      const std::string basePath = SETTINGS.spriteBasePath + "/objects/Warrior";
      auto idle = std::make_pair("idle", 5);
      auto walk = std::make_pair("walk", 8);

      std::vector<std::pair<std::string, int>> test{idle, walk};
      addObject(std::make_shared<CustomPlayer>(*this, x, y, 100, 50, 50, "Warrior", basePath, test));
    } else if (objectType == 'E') {
      auto idle = std::make_pair("idle", 12);
      auto walk = std::make_pair("walk", 6);
      const std::string basePath = SETTINGS.spriteBasePath + "/objects/Knight";

      std::vector<std::pair<std::string, int>> test{idle, walk};
      addObject(std::make_shared<CustomEnemy>(*this, x, y, 125, 25, 65, "Knight", basePath, test));
    } else if (objectType == 'M') {
      auto idle = std::make_pair("idle", 14);
      auto walk = std::make_pair("walk", 6);
      const std::string basePath = SETTINGS.spriteBasePath + "/objects/Mage";

      std::vector<std::pair<std::string, int>> test{idle, walk};
      addObject(std::make_shared<CustomEnemy>(*this, x, y, 100, 85, 25, "Mage", basePath, test));
    } else if (objectType == 'R') {
      auto idle = std::make_pair("idle", 15);
      auto walk = std::make_pair("walk", 5);
      const std::string basePath = SETTINGS.spriteBasePath + "/objects/Rock";

      std::vector<std::pair<std::string, int>> test{idle, walk};
      addObject(std::make_shared<CustomPassiveEnemy>(*this, x, y, 100, 85, 25, "Rock", basePath, test));
    } else if (objectType == 'K') {
      std::string powerupPath = SETTINGS.spriteBasePath + "/collectibles/Key";
      addObject(std::make_shared<CustomKey>(*this, x, y, powerupPath, "Key"));
    } else if (objectType == 'C') {
      std::string powerupPath = SETTINGS.spriteBasePath + "/collectibles/Coin";
      addObject(std::make_shared<CustomCoin>(*this, x, y, powerupPath, "Coin"));
    } else if (objectType == 'H') {
      std::string healthPath = SETTINGS.spriteBasePath + "/collectibles/Health";
      addObject(std::make_shared<CustomHealth>(*this, x, y, healthPath, "Health"));
    } else if (objectType == 'G') {
      addObject(std::make_shared<CustomGoal>(*this, x, y));
    } else if (objectType == 'L') {
      addObject(std::make_shared<CustomLaserDetector>(*this, x, y));
    }
  } else {
    addObject(std::make_shared<MapCell>(*this, x, y, objectType - '0'));
  }
}

/**
 * Re adds a player character into the level after a death.
 */
void CustomLevel::revive() {
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
        const std::string basePath = SETTINGS.spriteBasePath + "/objects/Warrior";
        auto idle = std::make_pair("idle", 5);
        auto walk = std::make_pair("walk", 8);

        std::vector<std::pair<std::string, int>> test{idle, walk};
        addObject(std::make_shared<CustomPlayer>(*this, initX, initY, 100, 50, 50, "Warrior", basePath, test));
      }
    }
  }
  SDL_Log("revived [state: %d]", state());
}

void CustomLevel::nextLevel() {
  if (useRandomLevel) {
    setInvincible(-1);

    setState(STATE_START);
    // mCollection = 0;
    std::cout << "Generating Random Map " << std::endl;
    // WORLD_MANAGER.nextLevel();
    int rows = 21;
    int cols = 11;
    uint64_t seed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    WORLD_MANAGER.setLevelName("RANDOM LEVEL");
    WORLD_MANAGER.setMapVector(CustomRandomLevelGenerator::generateLevel(rows, cols, seed));
    loadMap();
  } else {
    Level::nextLevel();
  }
}

void CustomLevel::toggleRandomLevelMode() {
  useRandomLevel = !useRandomLevel;
}
