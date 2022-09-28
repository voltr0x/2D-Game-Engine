#ifndef BASE_GAME_OBJECT
#define BASE_GAME_OBJECT

#include <SDL.h>
#include <memory>
#include <vector>
#include "base/AnimationsComponent.hpp"
#include "base/DisplayComponent.hpp"
#include "base/GenericComponent.hpp"
#include "base/PhysicsComponent.hpp"
#include "base/RenderComponent.hpp"
#include "base/SfxComponent.hpp"

class Level;

//! \brief Represents a GameObject in game. Chose to use an Object-Centric Architecture as it was the one used by the lab so we had a good starting point to work off and felt most comfortable with concepts surrounding it.
class GameObject : public std::enable_shared_from_this<GameObject> {
 public:
  GameObject(Level& level, float x, float y, float w, float h, int tag);
  virtual ~GameObject();

  inline int tag() const { return mTag; }
  inline void setTag(int tag) { mTag = tag; }
  inline int tagIndex() { return mTagIndex; }
  inline void setTagIndex(int ind) { mTagIndex = ind; }

  inline Level& getLevel() { return mLevel; }
  inline const Level& getLevel() const { return mLevel; }

  inline void setX(float x) { mX = x; }
  inline void setY(float y) { mY = y; }
  inline void setW(float w) { mW = w; }
  inline void setH(float h) { mH = h; }

  inline float x() const { return mX; }
  inline float y() const { return mY; }
  inline float w() const { return mW; }
  inline float h() const { return mH; }

  inline float initX() const { return mInitX; }
  inline float initY() const { return mInitY; }

  inline void addGenericCompenent(std::shared_ptr<GenericComponent> comp) { mGenericComponents.push_back(comp); }
  inline void setPhysicsCompenent(std::shared_ptr<PhysicsComponent> comp) { mPhysicsComponent = comp; }
  inline void setRenderCompenent(std::shared_ptr<RenderComponent> comp) { mRenderComponent = comp; }
  inline void setAnimationComponent(std::shared_ptr<AnimationsComponent> comp) { mAnimationComponent = comp; }
  inline void addSfxCompenent(std::shared_ptr<SfxComponent> comp) { mSfxComponents.push_back(comp); }
  inline void setDisplayCompenent(std::shared_ptr<DisplayComponent> comp) { mDisplayComponent = comp; }

  inline std::vector<std::shared_ptr<GenericComponent>> genericComponents() { return mGenericComponents; }
  inline std::shared_ptr<PhysicsComponent> physicsComponent() { return mPhysicsComponent; }
  inline std::shared_ptr<AnimationsComponent> animationComponent() const { return mAnimationComponent; }
  inline std::shared_ptr<RenderComponent> renderComponent() { return mRenderComponent; }
  inline std::vector<std::shared_ptr<SfxComponent>> sfxComponents() { return mSfxComponents; }
  inline std::shared_ptr<DisplayComponent> displayComponent() { return mDisplayComponent; }

  void update(Level& level);                                      //!< Update the object.
  void collision(Level& level, std::shared_ptr<GameObject> obj);  //!< Handle collisions with another object.
  void collision(std::shared_ptr<GameObject> obj);                //!< Handle collisions with another object using PhysicsManager.

  [[deprecated]] void step(Level& level);  //!< Do the physics step for the object.
  void postStep();                         //!< After the physics step for the object.

  void animate();                                      //!< Do the physics step for the object.
  void render(SDL_Renderer* renderer);                 //!< Render the object.
  void play(Level& level);                             //!< play sound effacts.
  void display(Level& level, SDL_Renderer* renderer);  //!< display info.

  bool isColliding(const GameObject& obj) const;  //!< Determine if this object is colliding with another.
  bool isColliding(float px, float py) const;     //!< Determine if this object is colliding with a point.

  inline bool isJump() { return jump && !onGround; }
  inline bool isOnGround() { return onGround; }
  inline bool isLeft() const { return left; }
  inline bool isRight() const { return right; }
  inline bool isGoUp() const { return goUp; }
  inline bool isGoDown() const { return goDown; }

  inline void setJump(bool j) {
    jump = j;
    if (!j) {
      onGround = true;
    }
  }
  inline void setOnGround(bool g) {
    onGround = g;
    if (g) {
      jump = false;
    }
  }
  inline void setLeft(bool l) { left = l; }
  inline void setRight(bool r) { right = r; }
  inline void setGoUp(bool up) { goUp = up; }
  inline void setGoDown(bool down) { goDown = down; }

  inline bool isDown() const { return down; }
  inline void setDown(bool d) { down = d; }

  inline bool isDead() const { return dead; }
  inline void die(bool d) { dead = d; }

 private:
  GameObject(const GameObject&) = delete;
  void operator=(GameObject const&) = delete;

  Level& mLevel;

  float mX, mY, mW, mH;
  float mInitX, mInitY;  //!< initial position used for reset
  int mTag, mTagIndex{0};

  std::vector<std::shared_ptr<GenericComponent>> mGenericComponents;
  std::shared_ptr<PhysicsComponent> mPhysicsComponent;
  std::shared_ptr<AnimationsComponent> mAnimationComponent;
  std::shared_ptr<RenderComponent> mRenderComponent;
  std::vector<std::shared_ptr<SfxComponent>> mSfxComponents;
  std::shared_ptr<DisplayComponent> mDisplayComponent;

  bool left{false}, right{false}, goUp{false}, goDown{false};
  bool jump{false}, onGround{true};
  // sprite state
  bool down{false};
  bool dead{false};
};

#endif
