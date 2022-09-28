#if !defined(WORLD_MANAGER_HPP)
#define WORLD_MANAGER_HPP

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "../base/Level.hpp"

class Level;

class WorldManager {
 private:
  WorldManager() = default;                      // Private Singleton
  WorldManager(WorldManager const&) = delete;    // Avoid copy constructor.
  void operator=(WorldManager const&) = delete;  // Don't allow copy assignment.
  WorldManager(WorldManager&&) = delete;         // Avoid move constructor.
  void operator=(WorldManager&&) = delete;       // Don't allow move assignment.
  /* data */
  std::vector<std::string> mLevelList;
  std::vector<std::vector<std::string>> mMapVector;
  std::string mLevelName{""};
  int currentLevel{0};
  int mRow{1}, mCol{1};
  int mLevelCount{0};

 public:
  static WorldManager& getInstance();

  inline std::vector<std::string> leveList() { return mLevelList; };
  inline std::vector<std::vector<std::string>> mapVector() { return mMapVector; };
  inline void setMapVector(std::vector<std::vector<std::string>> newMap) {  mMapVector = newMap;  };
  inline int row() { return mRow; }
  inline int col() { return mCol; }
  inline int getLevel() { return currentLevel % mLevelList.size() + 1; }

  inline std::string getLevelName() { return mLevelName; } 
  inline void setLevelName(std::string levelName) { mLevelName = levelName; }

  void init();
  void setLevel(int i);
  void nextLevel();
  std::vector<std::string> getLevelList();
  int getLevelCount() { return mLevelCount; }

  void loadCurrentLevel();

  void saveMap(Level& level);

  void saveMap(Level& level, int xOffset);

  // int getTagFromChar( std::string strChar);

  // std::string getCharFromTag(int tag);

  inline void updateMap(int indexX, int indexY, std::string strChar) {
    mMapVector[indexY][indexX] = strChar;
    std::cout << "UpdateMap => Row: " << indexY << ", Col:" << indexX << std::endl;
  };

  inline std::string getMapChar(int indexX, int indexY) {
    return mMapVector[indexY][indexX];
  };
};

#endif  // WORLD_MANAGER_HPP
