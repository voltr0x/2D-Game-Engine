#ifndef BASE_LEVEL
#define BASE_LEVEL

#include <SDL.h>
#include <memory>
#include <string>
#include <vector>
#include "GameObject.hpp"

//! \brief A level in the game.  Essentially mannages a collection of game
//! objects, and does some collision detection.
class Level {
 public:
  Level(int w, int h);
  virtual ~Level();
  virtual void initialize() = 0;
  void finalize();

  inline int w() const { return mW; }
  inline int h() const { return mH; }

  void addObject(std::shared_ptr<GameObject> object);     //!< Set an object to be added.
  void removeObject(std::shared_ptr<GameObject> object);  //!< Set an object to be removed.

  bool getCollisions(const GameObject& obj, std::vector<std::shared_ptr<GameObject>>& objects) const;  //!< Get objects colliding with a given object.
  bool getCollisions(float px, float py, std::vector<std::shared_ptr<GameObject>>& objects) const;     //!< Get objects colliding with a given point.

  // std::shared_ptr<GameObject>& findObject(float px, float py) const;

  void update();  //!< Update the objects in the level.
  void updateEditor();

  void render(SDL_Renderer* renderer);  //!< Render the level.

  void play();                           //!< play sound
  void display(SDL_Renderer* renderer);  //!< display infor

  inline void setFps(float fps) { mFps = fps; }
  inline float fps() { return mFps; }
  inline int collection() { return mCollection; }
  inline void decrementCollection() {  mCollection--;  }
  inline void collecting(int count) { mCollection += count; }
  
  //!< Updating player health
  inline int getPlayerHealth() { return mPlayerHealth; }
  inline void increaseHealth() { mPlayerHealth += 20; if(mPlayerHealth > 100){mPlayerHealth = 100;} }
  inline void decrementHealth() { mPlayerHealth -= 20; if(mPlayerHealth < 0){mPlayerHealth = 0;} }
  
  bool isCollecting();
  bool shouldPlayDeathSound();

  std::weak_ptr<GameObject> getTagged() {return tagged;}
  void setTagged(std::weak_ptr<GameObject> go) {tagged = go;}
  // game status
  inline void setState(int state) { mState = state; }
  inline int state() { return mState; }
  inline const int state() const { return mState; }

  inline void setTitle(std::string& title) { mTitle = title; }
  inline std::string title() { return mTitle; }
  inline bool isGameOver() { return mState >= 2; }

  inline int getTimer() { return timer; }
  inline int getLastInvincible() { return invinsible; }
  inline void setInvincible(int d) { invinsible = d; }

  inline int getShiftedMouseX() { return mShiftedMouseX; }
  inline void setShiftedMouseX(int d) { mShiftedMouseX = d; }
  inline int getShiftedMouseY() { return mShiftedMouseY; }
  inline void setShiftedMouseY(int d) { mShiftedMouseY = d; }

  inline int getSelectTag() { return mSelectTag; }
  inline void setSelectTag(int d) { mSelectTag = d; }

  inline std::string getLevelName() { return mLevelName; }
  inline void setLevelName(std::string d) { mLevelName = d; }

  inline int getLevelId() { return mLevelId; }
  inline void setLevelId(int d) { mLevelId = d; }

  inline bool isSaved() { return mSaved; }
  inline void setSaved(bool d) { mSaved = d; }

  inline int getAttack() { return attack; }
  inline void setAttack() { attack += 25; }
  inline int getDefense() { return defense; }
  inline void setDefense() { defense += 25; }

  inline bool getIsCombat() { return isCombat; }
  inline void setIsCombat(bool d) { isCombat = d; }
  inline std::vector<std::shared_ptr<GameObject>> getAllObjects() { return mObjects; }


  inline int getCoins() { return coins; }
  inline void addCoins(int d) { coins += d; }
  /**
   * @brief Restart game
   *
   */
  void reset();
  virtual void nextLevel();

  virtual void toggleRandomLevelMode() {};

  virtual void loadMap() = 0;
  virtual void revive() = 0;

  inline int getLives() { return mLives; }
  inline void setLives(int d) { mLives = d; }
  inline void lossLive() {
    mLives--;
    mState = 4;  // STATE_KILLED
    if (mLives <= 0) {
      mState = 3;  // STATE_LOSE
      mLives = 0;
    }
  }

 protected:
  bool mSaved{false};
  std::string mTitle{"Platformer"};
  std::string mLevelName{"Level 0"};
  int mLevelId{0};
  std::vector<std::shared_ptr<GameObject>> mObjects;
  std::vector<std::shared_ptr<GameObject>> mObjectsToAdd;
  std::vector<std::shared_ptr<GameObject>> mObjectsToRemove;

 private:
  Level(const Level&) = delete;
  void operator=(Level const&) = delete;

  int mW, mH;

  bool isCombat{false};

  float mFps;
  int timer{0};
  int coins{0};
  int attack{0};
  int defense{0};
  int mCollection{0};
  int mPlayerHealth{100};
  int mState{0};  //!< game state: 0; not start, 1: running, 2: win, 3, fallen, 4, killed 5, timeout
  int mLastScore{0};
  int invinsible{-1};
  bool mPlayedDeathSound{false};

  int mShiftedMouseX{0}, mShiftedMouseY{0};

  int mSelectTag{-1};
  int mLives{1};
  std::weak_ptr<GameObject> tagged;
};

#endif
