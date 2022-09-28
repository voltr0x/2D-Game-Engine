#if !defined(PLAYER_HPP)
#define PLAYER_HPP

#include <string>
#include <utility>
#include <vector>
#include "Globals.hpp"
#include "base/AnimationsComponent.hpp"
#include "base/GameObject.hpp"
#include "base/RenderSpriteComponent.hpp"
#include "platformer/components/PlatformerInputComponent.hpp"
#include "components/CollectOnCollideComponent.hpp"
#include "components/SoundComponent.hpp"

/**
 * @brief The goal object of the jump game.
 *
 */
class Player : public GameObject {
 public:
  Player(Level& level, float x, float y)
      : GameObject(level, x, y, SETTINGS.cellWidth, SETTINGS.cellHeight, TAG_PLAYER) {
    addGenericCompenent(std::make_shared<PlatformerInputComponent>(*this, 400.0f, 1000.0f, 80000.0f));
    // add sound component
    addSfxCompenent(std::make_shared<SoundComponent>(*this, REMOVE));
    addSfxCompenent(std::make_shared<SoundComponent>(*this, JUMP));
    addSfxCompenent(std::make_shared<SoundComponent>(*this, DIED));
    addGenericCompenent(std::make_shared<CollectOnCollideComponent>(*this, TAG_GOAL));
    addGenericCompenent(std::make_shared<CollectOnCollideComponent>(*this, TAG_COLLECTIBLE));
    addGenericCompenent(std::make_shared<CollectOnCollideComponent>(*this, TAG_POWERUP));

    setPhysicsCompenent(std::make_shared<PhysicsComponent>(*this, PhysicsComponent::Type::DYNAMIC_SOLID));

    const std::string basePath = SETTINGS.spriteBasePath + "/objects/Rogue";
    auto idle = std::make_pair("idle", 18);
    auto walk = std::make_pair("walk", 6);
    // auto walk = std::make_pair("run", 8);
    auto jump = std::make_pair("jump", 7);
    std::vector<std::pair<std::string, int>> test{idle, walk, jump};
    setAnimationComponent(std::make_shared<DynamicAnimationsComponent>(*this, basePath, test));
    setRenderCompenent(std::make_shared<RenderSpriteComponent>(*this, TAG_PLAYER));
  }

  Player(Level& level, float x, float y, int health, int attack, int defense)
      : GameObject(level, x, y, SETTINGS.cellWidth, SETTINGS.cellHeight, TAG_PLAYER) {
    addGenericCompenent(std::make_shared<PlatformerInputComponent>(*this, 500.0f, 5000.0f, 50000.0f));
    // add sound component
    addSfxCompenent(std::make_shared<SoundComponent>(*this, REMOVE));
    addSfxCompenent(std::make_shared<SoundComponent>(*this, JUMP));
    addSfxCompenent(std::make_shared<SoundComponent>(*this, DIED));
    addGenericCompenent(std::make_shared<CollectOnCollideComponent>(*this, TAG_GOAL));
    addGenericCompenent(std::make_shared<CollectOnCollideComponent>(*this, TAG_COLLECTIBLE));
    addGenericCompenent(std::make_shared<CollectOnCollideComponent>(*this, TAG_POWERUP));

    setPhysicsCompenent(std::make_shared<PhysicsComponent>(*this, PhysicsComponent::Type::DYNAMIC_SOLID));

    const std::string basePath = SETTINGS.spriteBasePath + "/objects/Rogue";
    auto idle = std::make_pair("idle", 18);
    auto walk = std::make_pair("walk", 6);
    // auto walk = std::make_pair("run", 8);
    auto jump = std::make_pair("jump", 7);
    std::vector<std::pair<std::string, int>> test{idle, walk, jump};
    setAnimationComponent(std::make_shared<DynamicAnimationsComponent>(*this, basePath, test));
    setRenderCompenent(std::make_shared<RenderSpriteComponent>(*this, TAG_PLAYER));

    health_ = health;
    attack_ = attack;
    defense_ = defense;
  }
  private:
  int health_, attack_, defense_;
};

#endif  // PLAYER_HPP
