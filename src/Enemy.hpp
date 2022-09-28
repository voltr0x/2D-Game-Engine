#if !defined(ENEMY_HPP)
#define ENEMY_HPP

#include "Globals.hpp"
#include "base/GameObject.hpp"
#include "base/RemoveOnCollideComponent.hpp"
#include "base/PatrolComponent.hpp"
#include "base/RenderSpriteComponent.hpp"
#include "base/AnimationsComponent.hpp"
#include "components/SoundComponent.hpp"
#include <utility>
#include <vector>
#include <string>

/**
 * @brief The goal object of the jump game.
 *
 */
class Enemy : public GameObject {
 public:
  inline Enemy(Level& level, float x, float y)
      : GameObject(level, x, y, SETTINGS.cellWidth, SETTINGS.cellHeight, TAG_ENEMY) {
    std::vector<std::pair<float,float>> locs;
    locs.emplace_back(std::make_pair(19 * SETTINGS.cellWidth, 4 * SETTINGS.cellHeight));

    addGenericCompenent(std::make_shared<PatrolComponent>(*this, locs, 500.0f));
    setPhysicsCompenent(std::make_shared<PhysicsComponent>(*this, PhysicsComponent::Type::STATIC_SENSOR));
    const std::string basePath = SETTINGS.spriteBasePath + "/objects/Knight";
    auto idle = std::make_pair("idle", 12);    
    auto walk = std::make_pair("walk", 6);
    auto jump = std::make_pair("jump", 7);
    std::vector<std::pair<std::string, int>> test{idle, walk, jump};
    setAnimationComponent(std::make_shared<DynamicAnimationsComponent>(*this, basePath, test));
    setRenderCompenent(std::make_shared<RenderSpriteComponent>(*this, TAG_ENEMY));
    addGenericCompenent(std::make_shared<RemoveOnCollideComponent>(*this, TAG_PLAYER));
    addSfxCompenent(std::make_shared<SoundComponent>(*this, DIED));
  }
};

#endif  // ENEMY_HPP
