#include "WorldManager.hpp"
//#include <dirent.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include "../Globals.hpp"
#include "../base/ResourcePath.hpp"

WorldManager& WorldManager::getInstance() {
  static WorldManager* instance = new WorldManager();
  return *instance;
}

void WorldManager::init() {
  mLevelList = getLevelList();
  mLevelCount = (int)mLevelList.size();

  std::cout << "WorldManager::init() ... ; levels = " << mLevelList.size() << std::endl;
  for (int i = 0; i < mLevelCount; ++i) {
    std::cout << mLevelList[i] << std::endl;
  }
  loadCurrentLevel();

  // update screen size
  SETTINGS.screenWidth = (mCol + SETTINGS.mapOffsetCol) * SETTINGS.cellWidth;
  SETTINGS.screenHeight = mRow * SETTINGS.cellHeight;
  if (SETTINGS.showTopBar) {
    SETTINGS.screenHeight += SETTINGS.topBarHeight;
  }
}

void WorldManager::nextLevel() {
  currentLevel++;
}

std::vector<std::string> WorldManager::getLevelList() {
  std::cout << "[WORLD]Read Level files[.txt] from: " << SETTINGS.levelListLocation << std::endl;
  // std::cout << "[Full Path]: " << getResourcePath(LEVEL_LOCATION) << std::endl;

  std::vector<std::string> fileNames;

  std::ifstream file(getResourcePath(SETTINGS.levelListLocation) + "/levelList.txt");
  std::string line;
  while (file >> line) {
    std::cout << "ADDING LEVEL LINE: " << line << "\n";
    fileNames.push_back(line);
  }

  return fileNames;
}
void WorldManager::setLevel(int i) {
  currentLevel = i;
}

void WorldManager::loadCurrentLevel() {
  std::cout << "World::loadCurrentLevel ==> start... " << std::endl;
  mMapVector.clear();
  std::string levelName = mLevelList[currentLevel % mLevelList.size()];
  std::string levelPath = getResourcePath(SETTINGS.levelListLocation.c_str()) + levelName;

  std::ifstream ifs;
  ifs.open(levelPath, std::ios::in);

  std::string line;
  int row = 0;
  while (getline(ifs, line)) {
    std::cout << line << std::endl;
    // first line: Level name
    if (row == 0) {
      mLevelName = line;
    } else {
      std::vector<std::string> lineVector;
      for (char c : line) {
        std::string block(1, c);
        lineVector.push_back(block);
      }
      mMapVector.push_back(lineVector);
    }
    row++;
  }

  mRow = mMapVector.size();
  mCol = mMapVector[0].size();
  std::cout << "World::loadCurrentLevel finished: " << currentLevel
            << " => " << mLevelName
            << "; Row: " << mRow << ", Col: " << mCol
            << std::endl;
}

void WorldManager::saveMap(Level& level) {
  saveMap(level, 0);
}

void WorldManager::saveMap(Level& level, int xOffset) {
  // std::vector<std::shared_ptr<GameObject>> allObjects = level.getAllObjects();
  std::stringstream fileName;
  fileName << SETTINGS.levelListLocation << "/" << getLevel() << ".txt";
  std::cout << "Save to: " << getResourceName(fileName.str().c_str()) << std::endl;
  std::ofstream outfile(getResourceName(fileName.str().c_str()), std::ios::trunc);

  std::cout << "Save map to:" << mLevelName << "; Row: " << mRow << ", Col:" << mCol << std::endl;
  outfile << mLevelName << "\n";

  for (size_t ii = 0; ii < (size_t)mRow; ii++) {
    for (size_t jj = 0; jj < (size_t)mCol; jj++) {
      std::cout << mMapVector[ii][jj] << "";
      outfile << mMapVector[ii][jj];
    }
    std::cout << std::endl;
    outfile << "\n";
  }
  outfile.close();

  std::cout << "==> Level saved!" << std::endl;
  level.setSaved(true);
}