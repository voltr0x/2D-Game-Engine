#if !defined(CUSTOM_OBJECTS_HPP)
#define CUSTOM_OBJECTS_HPP
#include <memory>

#include <sstream>
#include "../Globals.hpp"
#include "../base/GameObject.hpp"
#include "../base/PhysicsComponent.hpp"
#include "../base/PhysicsManager.hpp"
#include "../base/RenderBlockComponent.hpp"
#include "../base/RenderSpriteComponent.hpp"
#include "../components/CollectOnCollideComponent.hpp"
#include "../components/SoundComponent.hpp"
#include "../custom/components/CustomInputComponent.hpp"
#include "../custom/components/OpenOnCollideComponent.hpp"

/**
 * File for all the new objects in the custom game.
 */

/**
 * A key object.
 */
class CustomKey : public GameObject {
 public:
  CustomKey(Level& level, float x, float y, std::string basePath, std::string prefix)
      : GameObject(level, x, y, SETTINGS.cellWidth, SETTINGS.cellHeight, TAG_COLLECTIBLE) {
    setPhysicsCompenent(std::make_shared<PhysicsComponent>(*this, false));
    setAnimationComponent(std::make_shared<StaticAnimationsComponent>(*this, basePath, prefix, 1));
    setRenderCompenent(std::make_shared<RenderSpriteComponent>(*this, TAG_COLLECTIBLE));
  }
};

class CustomCoin : public GameObject {
 public:
  CustomCoin(Level& level, float x, float y, std::string basePath, std::string prefix)
      : GameObject(level, x, y, SETTINGS.cellWidth, SETTINGS.cellHeight, TAG_COIN) {
    setPhysicsCompenent(std::make_shared<PhysicsComponent>(*this, false));
    setAnimationComponent(std::make_shared<StaticAnimationsComponent>(*this, basePath, prefix, 1));
    setRenderCompenent(std::make_shared<RenderSpriteComponent>(*this, TAG_COIN));
  }
};
/**
 * A health potion object.
 */
class CustomHealth : public GameObject {
 public:
  CustomHealth(Level& level, float x, float y, std::string basePath, std::string prefix)
      : GameObject(level, x, y, SETTINGS.cellWidth, SETTINGS.cellHeight, TAG_HEALTH) {
    setPhysicsCompenent(std::make_shared<PhysicsComponent>(*this, false));
    setAnimationComponent(std::make_shared<StaticAnimationsComponent>(*this, basePath, prefix, 1));
    setRenderCompenent(std::make_shared<RenderSpriteComponent>(*this, TAG_HEALTH));
  }
};

/**
 * A door object.
 */
class CustomDoor : public GameObject {
 public:
  CustomDoor(Level& level, float x, float y)
      : GameObject(level, x, y, SETTINGS.cellWidth, SETTINGS.cellHeight, TAG_DOOR) {
    setPhysicsCompenent(std::make_shared<PhysicsComponent>(*this, PhysicsComponent::Type::STATIC_SOLID));

    std::stringstream blockSpriteName;
    blockSpriteName << SETTINGS.spriteBasePath << "/tiles/door.png";
    setRenderCompenent(std::make_shared<RenderBlockComponent>(*this, blockSpriteName.str()));
  }
};

/**
 * The player for the custom game. Has getter functions for heath, attack, defense, name and file path. Each of these are a private field as well.
 */

class CustomPlayer : public GameObject {
 public:
  CustomPlayer(Level& level, float x, float y, int health, int attack, int defense, std::string name)
      : GameObject(level, x, y, 55, 55, TAG_PLAYER) {
    std::string path = SETTINGS.spriteBasePath + "/objects/Warrior";
    std::vector<std::pair<std::string, int>> test{std::make_pair("idle", 5),
                                                  std::make_pair("walk", 8)};
    addGenericCompenent(std::make_shared<CustomInputComponent>(*this, 300.0f));
    // add sound component
    addSfxCompenent(std::make_shared<SoundComponent>(*this, REMOVE));
    addSfxCompenent(std::make_shared<SoundComponent>(*this, DIED));

    addGenericCompenent(std::make_shared<CollectOnCollideComponent>(*this, TAG_COLLECTIBLE));
    addGenericCompenent(std::make_shared<CollectOnCollideComponent>(*this, TAG_COIN));
    addGenericCompenent(std::make_shared<CollectOnCollideComponent>(*this, TAG_HEALTH));
    addGenericCompenent(std::make_shared<OpenOnCollideComponent>(*this, TAG_DOOR));

    setPhysicsCompenent(std::make_shared<PhysicsComponent>(*this, PhysicsComponent::Type::DYNAMIC_SOLID));

    setAnimationComponent(std::make_shared<DynamicAnimationsComponent>(*this, path, test));
    setRenderCompenent(std::make_shared<RenderSpriteComponent>(*this, TAG_PLAYER_1));

    health_ = health;
    attack_ = attack;
    defense_ = defense;
    name_ = name;
    path_ = path + "/idle/idle1.png";
  }

  CustomPlayer(Level& level, float x, float y, int health, int attack, int defense, std::string name, std::string path, std::vector<std::pair<std::string, int>> test)
      : GameObject(level, x, y, 55, 55, TAG_PLAYER) {
    addGenericCompenent(std::make_shared<CustomInputComponent>(*this, 300.0f));
    // add sound component
    addSfxCompenent(std::make_shared<SoundComponent>(*this, REMOVE));
    addSfxCompenent(std::make_shared<SoundComponent>(*this, DIED));

    addGenericCompenent(std::make_shared<CollectOnCollideComponent>(*this, TAG_GOAL));
    addGenericCompenent(std::make_shared<CollectOnCollideComponent>(*this, TAG_COLLECTIBLE));
    addGenericCompenent(std::make_shared<CollectOnCollideComponent>(*this, TAG_HEALTH));
    addGenericCompenent(std::make_shared<CollectOnCollideComponent>(*this, TAG_COIN));
    addGenericCompenent(std::make_shared<OpenOnCollideComponent>(*this, TAG_DOOR));
    addGenericCompenent(std::make_shared<AttackComponent>(*this, TAG_ENEMY));

    setPhysicsCompenent(std::make_shared<PhysicsComponent>(*this, PhysicsComponent::Type::DYNAMIC_SOLID));

    setAnimationComponent(std::make_shared<DynamicAnimationsComponent>(*this, path, test));
    setRenderCompenent(std::make_shared<RenderSpriteComponent>(*this, TAG_PLAYER_1));

    health_ = health;
    attack_ = attack;
    defense_ = defense;
    name_ = name;
    path_ = path + "/idle/idle1.png";
  }
  int getHealth() { return health_; }
  int getAttack() { return attack_; }
  int getDefense() { return defense_; }
  std::string getName() { return name_; }
  std::string getPath() { return path_; }

  void setHealth(int i) { health_ += i; }
  void setAttack(int i) { attack_ += i; }
  void setDefense(int i) { defense_ += i; }

 private:
  int health_;
  int attack_;
  int defense_;
  std::string name_;
  std::string path_;
};

/**
 * Same implementation as the player but without input, sfx and collision components.
 */

class CustomEnemy : public GameObject {
 public:
  CustomEnemy(Level& level, float x, float y, int health, int attack, int defense, std::string name)
      : GameObject(level, x, y, SETTINGS.cellWidth, SETTINGS.cellHeight, TAG_ENEMY) {
    std::string path = SETTINGS.spriteBasePath + "/objects/Mage";
    std::vector<std::pair<std::string, int>> test{std::make_pair("idle", 14),
                                                  std::make_pair("walk", 6)};
    setPhysicsCompenent(std::make_shared<PhysicsComponent>(*this, PhysicsComponent::Type::STATIC_SOLID));

    setAnimationComponent(std::make_shared<DynamicAnimationsComponent>(*this, path, test));
    setRenderCompenent(std::make_shared<RenderSpriteComponent>(*this, TAG_ENEMY));

    health_ = health;
    attack_ = attack;
    defense_ = defense;
    name_ = name;
    path_ = path + "/idle/idle1.png";
  }

  CustomEnemy(Level& level, float x, float y, int health, int attack, int defense, std::string name, std::string path, std::vector<std::pair<std::string, int>> test)
      : GameObject(level, x, y, SETTINGS.cellWidth, SETTINGS.cellHeight, TAG_ENEMY) {
    setPhysicsCompenent(std::make_shared<PhysicsComponent>(*this, PhysicsComponent::Type::STATIC_SOLID));

    setAnimationComponent(std::make_shared<DynamicAnimationsComponent>(*this, path, test));
    setRenderCompenent(std::make_shared<RenderSpriteComponent>(*this, TAG_ENEMY));

    health_ = health;
    attack_ = attack;
    defense_ = defense;
    name_ = name;
    path_ = path + "/idle/idle1.png";
  }
  int getHealth() { return health_; }
  int getAttack() { return attack_; }
  int getDefense() { return defense_; }
  std::string getName() { return name_; }
  std::string getPath() { return path_; }

  void setHealth(int i) { health_ += i; }

 private:
  int health_;
  int attack_;
  int defense_;
  std::string name_;
  std::string path_;
};

/**
 * Same implementation for a custom enemy who does not take damage.
 */

class CustomPassiveEnemy : public GameObject {
 public:
  CustomPassiveEnemy(Level& level, float x, float y, int health, int attack, int defense, std::string name)
      : GameObject(level, x, y, SETTINGS.cellWidth, SETTINGS.cellHeight, TAG_PASSIVE_ENEMY) {
    std::string path = SETTINGS.spriteBasePath + "/objects/Rock";
    std::vector<std::pair<std::string, int>> test{std::make_pair("idle", 15),
                                                  std::make_pair("walk", 5)};
    setPhysicsCompenent(std::make_shared<PhysicsComponent>(*this, PhysicsComponent::Type::STATIC_SOLID));
    // addGenericCompenent(std::make_shared<AttackComponent>(*this, TAG_PLAYER));

    setAnimationComponent(std::make_shared<DynamicAnimationsComponent>(*this, path, test));
    setRenderCompenent(std::make_shared<RenderSpriteComponent>(*this, TAG_PASSIVE_ENEMY));

    health_ = health;
    attack_ = attack;
    defense_ = defense;
    name_ = name;
    path_ = path + "/idle/idle1.png";
  }

  CustomPassiveEnemy(Level& level, float x, float y, int health, int attack, int defense, std::string name, std::string path, std::vector<std::pair<std::string, int>> test)
      : GameObject(level, x, y, SETTINGS.cellWidth, SETTINGS.cellHeight, TAG_PASSIVE_ENEMY) {
    setPhysicsCompenent(std::make_shared<PhysicsComponent>(*this, PhysicsComponent::Type::STATIC_SOLID));
    // addGenericCompenent(std::make_shared<AttackComponent>(*this, TAG_PLAYER));

    setAnimationComponent(std::make_shared<DynamicAnimationsComponent>(*this, path, test));
    setRenderCompenent(std::make_shared<RenderSpriteComponent>(*this, TAG_PASSIVE_ENEMY));

    health_ = health;
    attack_ = attack;
    defense_ = defense;
    name_ = name;
    path_ = path + "/idle/idle1.png";
  }
  int getHealth() { return health_; }
  int getAttack() { return attack_; }
  int getDefense() { return defense_; }
  std::string getName() { return name_; }
  std::string getPath() { return path_; }

  void setHealth(int i) { health_ += i; }

 private:
  int health_;
  int attack_;
  int defense_;
  std::string name_;
  std::string path_;
};

class CustomLaserDetector : public GameObject {
 public:
  CustomLaserDetector(Level& level, float x, float y)
      : GameObject(level, x, y, SETTINGS.cellWidth, SETTINGS.cellHeight, TAG_DETECTOR) {
    setPhysicsCompenent(std::make_shared<PhysicsComponent>(*this, PhysicsComponent::Type::STATIC_SENSOR));
    std::string path = SETTINGS.spriteBasePath + "/tiles/detector.png";
    setRenderCompenent(std::make_shared<RenderSpriteComponent>(*this, path, TAG_DETECTOR));

    addGenericCompenent(std::make_shared<AttackComponent>(*this, TAG_PLAYER));
  }
};

/**

* @brief The goal object of the jump game.
*
*/
class CustomGoal : public GameObject {
 public:
  CustomGoal(Level& level, float x, float y)
      : GameObject(level, x, y, SETTINGS.cellWidth, SETTINGS.cellHeight, TAG_GOAL) {
    setPhysicsCompenent(std::make_shared<PhysicsComponent>(*this, false));
    std::string path = SETTINGS.spriteBasePath + "/tiles/stairs.png";
    setRenderCompenent(std::make_shared<RenderSpriteComponent>(*this, path, TAG_GOAL));
    setDown(true);
  }
};
#endif  // CUSTOM_OBJECTS_HPP
