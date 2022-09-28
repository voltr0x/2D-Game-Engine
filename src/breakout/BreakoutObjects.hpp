#if !defined(BREAKOUT_OBJECTS_HPP)
#define BREAKOUT_OBJECTS_HPP
#include <memory>

#include <sstream>
#include "../Globals.hpp"
#include "../base/GameObject.hpp"
#include "../base/PhysicsComponent.hpp"
#include "../base/PhysicsManager.hpp"
#include "../base/RenderBlockComponent.hpp"
#include "../components/SoundComponent.hpp"
#include "components/BounceOnCollideComponent.hpp"
#include "components/BreakOnCollideComponent.hpp"
#include "components/BreakoutInputComponent.hpp"
#include "components/KilledOnCollideComponent.hpp"

const int brickWidth = 100;
const int brickHeight = 25;

const int paddleWidth = 220;
const int paddleHeight = 20;

const int ballWidth = 20;
const int ballHeight = 20;

class BreakoutBrick : public GameObject {
 public:
  BreakoutBrick(Level& level, int c, float x, float y)
      : GameObject(level, x, y, brickWidth, brickHeight, TAG_BLOCK) {
    setPhysicsCompenent(std::make_shared<PhysicsComponent>(*this, true));
    std::stringstream brickName;  // TODO move to settings
    brickName << SETTINGS.spriteBasePath << "/brick" << c << ".bmp";
    setRenderCompenent(std::make_shared<RenderBlockComponent>(*this, brickName.str()));
  }
};

class BreakoutPaddle : public GameObject {
 public:
  BreakoutPaddle(Level& level, float x, float y)
      : GameObject(level, x, y, paddleWidth, paddleHeight, TAG_PLAYER) {
    std::stringstream paddlePath;  // TODO move to settings
    paddlePath << SETTINGS.spriteBasePath << "/paddle.bmp";
    setRenderCompenent(std::make_shared<RenderBlockComponent>(*this, paddlePath.str()));
    // b2_dynamicBody
    setPhysicsCompenent(std::make_shared<PhysicsComponent>(*this, PhysicsComponent::Type::DYNAMIC_SOLID, 10000.0f, 0.4f, 0.1f));
    addGenericCompenent(std::make_shared<BreakoutInputComponent>(*this, 500.0f, 0.0f, 0.0f));
  }
};

class BreakoutBall : public GameObject {
 public:
  BreakoutBall(Level& level, float x, float y)
      : GameObject(level, x, y, ballWidth, ballHeight, TAG_BALL) {
    std::stringstream ballPath;
    ballPath << SETTINGS.spriteBasePath << "/ball.bmp";
    setRenderCompenent(std::make_shared<RenderBlockComponent>(*this, ballPath.str()));
    // b2_dynamicBody
    setPhysicsCompenent(std::make_shared<PhysicsComponent>(*this, PhysicsComponent::Type::DYNAMIC_SOLID, 1.0f, 0.0f, 1.0f));
    addGenericCompenent(std::make_shared<BounceOnCollideComponent>(*this, 300.0f));
    addGenericCompenent(std::make_shared<BreakOnCollideComponent>(*this, TAG_BLOCK));
    // TODO may add sound when brick is removed
  }
};

class DeadZone : public GameObject {
 public:
  DeadZone(Level& level, std::vector<int>& box)
      : GameObject(level, box[0], box[1], box[2], box[3], TAG_DEAD_ZONE) {
    setPhysicsCompenent(std::make_shared<PhysicsComponent>(*this, false));
    addGenericCompenent(std::make_shared<KilledOnCollideComponent>(*this, TAG_BALL));
    addSfxCompenent(std::make_shared<SoundComponent>(*this, DIED));
  }
};

#endif  // BREAKOUT_OBJECTS_HPP
