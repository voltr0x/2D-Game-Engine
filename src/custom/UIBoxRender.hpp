#if !defined(UI_BOX_RENDER_HPP)
#define UI_BOX_RENDER_HPP

#include <sstream>
#include "../Globals.hpp"
#include "../base/DisplayComponent.hpp"
#include "../base/GameObject.hpp"
#include "CustomObjects.hpp"

/**
 * The render class for the UI box.
 */
class UIBoxRender : public DisplayComponent {
 public:
  // Sets up the dimenstions and placement of the box.
  inline UIBoxRender(GameObject& gameObject)
      : DisplayComponent(gameObject) {
    mBoxX = gameObject.x();
    mBoxY = gameObject.y();

    mBoxW = int(3 * SETTINGS.cellWidth);
    mBoxH = int(WORLD_MANAGER.row() * SETTINGS.cellHeight);
    mBorderSize = 2;

    gameObject.setW(mBoxW);
    gameObject.setH(mBoxH);
  }

  /**
   * Renders player or enemy info based on isPlayer.
   */
  template <typename T>
  void displayHelp(Level& level, SDL_Renderer* renderer, int x, int y, T* obj, bool isPlayer) {
    TTF_Font* mFont = RESOURCE_MANAGER.getFont(FONT_NORMAL, 24);
    // player inf&o
    std::stringstream nameText;
    if (!obj) {
      nameText << "Enemy: Click One";
    } else if (isPlayer) {
      nameText << "Player: " << obj->getName();
    } else {
      nameText << "Enemy: " << obj->getName();
    }
    TextTexture* nameTexture = RESOURCE_MANAGER.getTextTexture(mFont, nameText.str().c_str(), {255, 255, 0, 255});
    nameTexture->render(renderer, 5, y);

    if (!obj) {
      return;
    }

    SDL_Rect renderQuad = {x, y += 30, SETTINGS.cellWidth, SETTINGS.cellHeight};
    SDL_Rect clip = {20, 60, 50, 50};
    SDL_RenderCopy(renderer, RESOURCE_MANAGER.getTexture(obj->getPath()), &clip, &renderQuad);

    // // health info
    std::stringstream healthText;
    healthText << "HP: " << obj->getHealth();
    //healthText << "HP: " << level.getPlayerHealth();
    TextTexture* healthTexture = RESOURCE_MANAGER.getTextTexture(mFont, healthText.str().c_str(), {255, 255, 0, 255});
    healthTexture->render(renderer, x, y += (SETTINGS.cellHeight + 25));

    renderQuad = {x - 35, y, 25, 25};
    std::string healthPath = SETTINGS.spriteBasePath + "/ui/health.png";
    SDL_RenderCopy(renderer, RESOURCE_MANAGER.getTexture(healthPath), NULL, &renderQuad);

    // attack info

    std::stringstream attackText;
    int attack = isPlayer ? obj->getAttack() + level.getAttack() : obj->getAttack();
    attackText << "ATK: " << attack;
    TextTexture* attackTexture = RESOURCE_MANAGER.getTextTexture(mFont, attackText.str().c_str(), {255, 255, 0, 255});
    attackTexture->render(renderer, x, y += 25);

    renderQuad = {x - 35, y, 25, 25};
    std::string attackPath = SETTINGS.spriteBasePath + "/ui/attack.png";
    SDL_RenderCopy(renderer, RESOURCE_MANAGER.getTexture(attackPath), NULL, &renderQuad);

    // defense info
    std::stringstream defenseText;
    int defense = isPlayer ? obj->getDefense() + level.getDefense() : obj->getDefense();
    defenseText << "DEF: " << defense;
    TextTexture* defenseTexture = RESOURCE_MANAGER.getTextTexture(mFont, defenseText.str().c_str(), {255, 255, 0, 255});
    defenseTexture->render(renderer, x, y += 25);

    renderQuad = {x - 35, y, 25, 25};
    std::string defensePath = SETTINGS.spriteBasePath + "/ui/defense.png";
    SDL_RenderCopy(renderer, RESOURCE_MANAGER.getTexture(defensePath), NULL, &renderQuad);


    // coin info
    if (isPlayer) {
    std::stringstream coinsText;
    coinsText << "Coins: " << level.getCoins();
    TextTexture* coinsTexture = RESOURCE_MANAGER.getTextTexture(mFont, coinsText.str().c_str(), {255, 255, 0, 255});
    coinsTexture->render(renderer, x, y += 25);

    renderQuad = {x - 35, y, 25, 25};
    std::string coinsPath = SETTINGS.spriteBasePath + "/ui/coin.png";
    SDL_RenderCopy(renderer, RESOURCE_MANAGER.getTexture(coinsPath), NULL, &renderQuad);
    }
  }

  /**
   * If the gameObject is the UI_BOX draw the box rectangle.
   * Calls displayHelp() to display more specific info for the enemy and player.
   */
  inline virtual void display(Level& level, SDL_Renderer* renderer) override {
    GameObject& gameObject = getGameObject();
    // render tool box
    if (gameObject.tag() == TAG_PLAYER_UI_BOX) {
      SDL_Rect drawRect = {mBoxX, mBoxY, mBoxW, mBoxH};
      SDL_SetRenderDrawColor(renderer, 0x40, 0x40, 0x40, 0xFF);
      SDL_RenderDrawRect(renderer, &drawRect);

      drawRect = {mBoxX + mBorderSize, mBoxY + mBorderSize, mBoxW - mBorderSize * 2, mBoxH - mBorderSize * 2};
      SDL_SetRenderDrawColor(renderer, 0x22, 0x22, 0x22, 0xFF);
      SDL_RenderFillRect(renderer, &drawRect);
    }

    int x = 60;
    int y = gameObject.y() + 100;

    std::shared_ptr<GameObject> playerGO;
    for (auto& a : level.getAllObjects()) {
      if (a->tag() == TAG_PLAYER) {
        playerGO = a;
      }
    }
    if (playerGO == nullptr) {
      return;
    }
    auto t = playerGO.get();
    CustomPlayer* player = dynamic_cast<CustomPlayer*>(t);
    displayHelp(level, renderer, x, y, player, true);
    y += 250;
    std::weak_ptr<GameObject> e = level.getTagged();
    std::shared_ptr<GameObject> se = e.lock();
    CustomEnemy* enemy = nullptr;
    if (se) {
      auto tt = se.get();
      enemy = dynamic_cast<CustomEnemy*>(tt);
    }
    displayHelp(level, renderer, x, y, enemy, false);
  }

  /**
   * private fields for the UI window componenets.
   */
 private:
  int mBoxX, mBoxY;
  int mBoxW, mBoxH;
  int mBorderSize;
};

#endif  // EDITOR_TOOL_BOX_RENDER_HPP