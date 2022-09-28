#include "CollectOnCollideComponent.hpp"
#include "../Globals.hpp"
#include "../base/Level.hpp"
#include "../custom/CustomObjects.hpp"

CollectOnCollideComponent::CollectOnCollideComponent(GameObject &gameObject, int tag)
    : GenericComponent(gameObject),
      mTag(tag)
{
}

AttackComponent::AttackComponent(GameObject &gameObject, int tag)
    : GenericComponent(gameObject),
      mTag(tag)
{
}
void AttackComponent::collision(Level &level, std::shared_ptr<GameObject> obj)
{
  if (level.getTimer() % 5 != 0)
  {
    return;
  }
  if (obj->tag() == mTag)
  {
    switch (mTag)
    {
    case TAG_ENEMY:
    {
      level.setTagged(obj);
      level.setIsCombat(true);

      std::shared_ptr<GameObject> playerGO;
      for (auto &a : level.getAllObjects())
      {
        if (a->tag() == TAG_PLAYER)
        {
          playerGO = a;
          break;
        }
      }
      auto t = playerGO.get();
      CustomPlayer *player = dynamic_cast<CustomPlayer *>(t);
      auto tt = obj.get();
      CustomEnemy *enemy = dynamic_cast<CustomEnemy *>(tt);
      float pH = float(enemy->getAttack()) / float(player->getDefense() + level.getDefense()) * 10;
      float eH = float(player->getAttack() + level.getAttack()) / float(enemy->getDefense()) * 10;
      player->setHealth(-int(pH));
      enemy->setHealth(-int(eH));
      // player dies
      if (enemy->getHealth() <= 0)
      {
        level.removeObject(obj);
        level.setIsCombat(false);
      }
      if (player->getHealth() <= 0)
      {
        level.setState(STATE_KILLED);
        level.setIsCombat(false);
      }
      break;
    }
    case TAG_PASSIVE_ENEMY:
    {
      level.setTagged(obj);
      level.setIsCombat(true);

      std::shared_ptr<GameObject> playerGO;
      for (auto &a : level.getAllObjects())
      {
        if (a->tag() == TAG_PLAYER)
        {
          playerGO = a;
          break;
        }
      }
      auto t = playerGO.get();
      CustomPlayer *player = dynamic_cast<CustomPlayer *>(t);
      auto tt = obj.get();
      CustomPassiveEnemy *passiveEnemy = dynamic_cast<CustomPassiveEnemy *>(tt);
      float pH = float(passiveEnemy->getAttack()) / float(player->getDefense() + level.getDefense()) * 10;
      float eH = float(player->getAttack() + level.getAttack()) / float(passiveEnemy->getDefense()) * 10;
      player->setHealth(-int(pH));
      passiveEnemy->setHealth(-int(eH));
      // player dies
      if (passiveEnemy->getHealth() <= 0)
      {
        level.removeObject(obj);
        level.setIsCombat(false);
      }
      if (player->getHealth() <= 0)
      {
        level.setState(STATE_KILLED);
        level.setIsCombat(false);
      }
      break;
    }
    case TAG_PLAYER:
      level.setIsCombat(true);
      std::shared_ptr<GameObject> o;
      for (auto &a : level.getAllObjects())
      {
        if (a->tag() == TAG_PASSIVE_ENEMY)
        {
          o = a;
          break;
        }
      }
      auto obj1 = o.get();
      auto animate = obj1->animationComponent();
      auto a = animate.get();
      if(a->getCount() / 10 %15 + 1 >= 10) {
        level.setState(STATE_KILLED);
      }
      break;
    }
  }
}

void CollectOnCollideComponent::collision(Level &level, std::shared_ptr<GameObject> obj)
{
  if (obj->tag() == mTag)
  {
    switch (mTag)
    {
    case TAG_HEALTH:
    {
      std::shared_ptr<GameObject> playerGO;
      for (auto &a : level.getAllObjects())
      {
        if (a->tag() == TAG_PLAYER)
        {
          playerGO = a;
          break;
        }
      }
      auto t = playerGO.get();
      CustomPlayer *player = dynamic_cast<CustomPlayer *>(t);
      player->setHealth(50);
      level.removeObject(obj);
      break;
    }
    case TAG_COLLECTIBLE:
      level.collecting(1);
      level.removeObject(obj);
      break;
    case TAG_COIN:
      level.addCoins(100);
      level.removeObject(obj);
      break;
    case TAG_POWERUP:
      level.setInvincible(level.getTimer());
      level.removeObject(obj);
      break;
    case TAG_GOAL:
      if (obj->isDown())
      {
        obj->setDown(false);
        level.setState(STATE_WIN);
        // obj->setTag(TAG_GENERAL);
      }
      break;
    }
  }
}
