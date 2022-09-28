#if !defined(MAP_OBJECTS_HPP)
#define MAP_OBJECTS_HPP

#include "base/AnimationsComponent.hpp"
#include "base/GameObject.hpp"
#include "base/GridRenderComponent.hpp"
#include "base/Level.hpp"
#include "base/RemoveOnCollideComponent.hpp"
#include "base/RenderBlockComponent.hpp"
#include "base/RenderSpriteComponent.hpp"
#include "base/SDLGraphicsProgram.hpp"
#include "components/ScreenComponent.hpp"
#include "components/SoundComponent.hpp"
#include "components/SpriteGoalComponent.hpp"

class MapGrid : public GameObject {
 public:
  MapGrid(Level& level, int xsz, int ysz)
      : GameObject(level, -1, -1, xsz * SETTINGS.cellWidth, ysz * SETTINGS.cellHeight, TAG_IGNORE) {
    float _y = this->y();

    SDL_Log("#1 MapGrid: y: %f", _y);

    this->setX(this->x() + (SETTINGS.mapOffsetCol * SETTINGS.cellWidth));
    if (SETTINGS.showTopBar) {
      _y += SETTINGS.topBarHeight;
    }
    this->setY(_y + (SETTINGS.mapOffsetRow * SETTINGS.cellHeight));

    setRenderCompenent(std::make_shared<GridRenderComponent>(*this, CELL_SIZE, xsz, ysz));

    SDL_Log("#2 MapGrid: y(): %f; x(): %f", this->y(), this->x());
  }
};

class SoundEffects : public GameObject {
 public:
  SoundEffects(Level& level, SFX sfxType)
      : GameObject(level, 0, 0, 0, 0, TAG_GENERAL) {
    addSfxCompenent(std::make_shared<SoundComponent>(*this, sfxType));
  }
};

class Displayer : public GameObject {
 public:  // TODO add more TAGs for sound, display component
  Displayer(Level& level)
      : GameObject(level, 0, 0, 0, 0, TAG_IGNORE) {
    if (SETTINGS.showTopBar) {
      this->setY(this->y() + SETTINGS.topBarHeight);
    }
    setDisplayCompenent(std::make_shared<ScreenComponent>(*this));
  }
};

/**
 * @brief The goal object of the jump game.
 *
 */
class Goal : public GameObject {
 public:
  Goal(Level& level, float x, float y)
      : GameObject(level, x, y, SETTINGS.cellWidth, SETTINGS.cellHeight, TAG_GOAL) {
    setPhysicsCompenent(std::make_shared<PhysicsComponent>(*this, false));

    setRenderCompenent(std::make_shared<SpriteGoalComponent>(*this));
  }
};

class Collectible : public GameObject {
 public:
  Collectible(Level& level, float x, float y, std::string basePath, std::string prefix)
      : GameObject(level, x, y, SETTINGS.cellWidth, SETTINGS.cellHeight, TAG_COLLECTIBLE) {
    setPhysicsCompenent(std::make_shared<PhysicsComponent>(*this, false));
    setAnimationComponent(std::make_shared<StaticAnimationsComponent>(*this, basePath, prefix, 30));
    setRenderCompenent(std::make_shared<RenderSpriteComponent>(*this, TAG_COLLECTIBLE));
  }
};

class Powerup : public GameObject {
 public:
  Powerup(Level& level, float x, float y, std::string basePath, std::string prefix)
      : GameObject(level, x, y, SETTINGS.cellWidth, SETTINGS.cellHeight, TAG_POWERUP) {
    setPhysicsCompenent(std::make_shared<PhysicsComponent>(*this, false));
    // addSfxCompenent(std::make_shared<SoundComponent>(*this, REMOVE));
    setAnimationComponent(std::make_shared<StaticAnimationsComponent>(*this, basePath, prefix, 30));
    setRenderCompenent(std::make_shared<RenderSpriteComponent>(*this, TAG_POWERUP));
  }
};

/**
 * @brief The block object for creating blocks.
 *
 */
class DeathBox : public GameObject {
 public:
  DeathBox(Level& level, std::vector<int>& box)
      : GameObject(level, box[0], box[1], box[2], box[3], TAG_TRIGGER_ZONE) {
    setPhysicsCompenent(std::make_shared<PhysicsComponent>(*this, false));
    addGenericCompenent(std::make_shared<RemoveOnCollideComponent>(*this, TAG_PLAYER));
    addSfxCompenent(std::make_shared<SoundComponent>(*this, DIED));
    setRenderCompenent(std::make_shared<RenderSpriteComponent>(*this, TAG_TRIGGER_ZONE));
  }
};

class BorderBox : public GameObject {
 public:
  BorderBox(Level& level, std::vector<int>& box, int tag)
      : GameObject(level, box[0], box[1], box[2], box[3], tag) {
    if (tag == TAG_TRIGGER_ZONE) {
      addGenericCompenent(std::make_shared<RemoveOnCollideComponent>(*this, TAG_PLAYER));
      addSfxCompenent(std::make_shared<SoundComponent>(*this, DIED));
      setPhysicsCompenent(std::make_shared<PhysicsComponent>(*this, false));
    } else {
      setPhysicsCompenent(std::make_shared<PhysicsComponent>(*this, true));
    }
    setRenderCompenent(std::make_shared<RenderSpriteComponent>(*this, tag));
  }
};

#endif  // MAP_OBJECTS_HPP
