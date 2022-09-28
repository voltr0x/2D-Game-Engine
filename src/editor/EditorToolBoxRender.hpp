#if !defined(EDITOR_TOOL_BOX_RENDER_HPP)
#define EDITOR_TOOL_BOX_RENDER_HPP

#include <sstream>
#include "../Globals.hpp"
#include "../base/DisplayComponent.hpp"
#include "../base/GameObject.hpp"

class EditorToolBoxRender : public DisplayComponent {
 public:
  inline EditorToolBoxRender(GameObject& gameObject)
      : DisplayComponent(gameObject) {
    mBoxX = gameObject.x();
    mBoxY = gameObject.y();
    mBoxW = gameObject.w();
    mBoxH = gameObject.h();
    mBorderSize = 5;
  }

  inline virtual void display(Level& level, SDL_Renderer* renderer) override {
    GameObject& gameObject = getGameObject();
    TTF_Font* mFont = RESOURCE_MANAGER.getFont(FONT_NORMAL, 24);
    // render tool box
    if (gameObject.tag() == TAG_EDITOR_TOOL_BOX) {
      SDL_Rect drawRect = {mBoxX, mBoxY, mBoxW, mBoxH};
      SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, 0x99);
      SDL_RenderDrawRect(renderer, &drawRect);

      SDL_SetRenderDrawColor(renderer, 0xff, 0x22, 0x22, 0xFF);
      SDL_RenderFillRect(renderer, &drawRect);

      drawRect = {mBoxX + mBorderSize, mBoxY + mBorderSize, mBoxW - mBorderSize * 2, mBoxH - mBorderSize * 2};
      SDL_SetRenderDrawColor(renderer, 0x22, 0x22, 0x22, 0xFF);
      SDL_RenderFillRect(renderer, &drawRect);
    } else if (gameObject.tag() == TAG_EDITOR_LEVEL) {
      // level choose buttons
      int shirink = 5;
      SDL_Rect drawRect = {int(gameObject.x()) + shirink, int(gameObject.y()) + shirink * 2, SETTINGS.cellSize - shirink * 2, SETTINGS.cellSize - shirink * 4};
      if (level.getLevelId() - 1 == gameObject.tagIndex()) {
        /* code */
        SDL_SetRenderDrawColor(renderer, 255, 100, 0, 255);
      } else {
        SDL_SetRenderDrawColor(renderer, 0x99, 0x99, 0x99, 0x99);
      }
      SDL_RenderFillRect(renderer, &drawRect);
      // render

      TTF_Font* mFont_1 = RESOURCE_MANAGER.getFont(FONT_NORMAL, 18);
      std::stringstream mText;
      mText << "Level " << gameObject.tagIndex() + 1;
      TextTexture* mTextTexture = RESOURCE_MANAGER.getTextTexture(mFont_1, mText.str().c_str(), {0, 0, 255, 255});
      mTextTexture->render(renderer, gameObject.x() + 7, gameObject.y() + 20);

    } else {
      // spirate intital position related the box position
      bool nullClip = false;
      SDL_Rect clip = {20, 60, 50, 50};
      SDL_Rect renderQuad = {int(gameObject.x()), int(gameObject.y()), SETTINGS.cellWidth, SETTINGS.cellHeight};
      std::string spriteFileName = "";

      if (gameObject.tag() == TAG_EDITOR_PLAYER) {
        std::string playerFileName = SETTINGS.spriteBasePath + "/objects/Rogue/idle/idle1.png";
        spriteFileName = playerFileName;
      } else if (gameObject.tag() == TAG_EDITOR_ENEMY) {
        std::string enemyFileName = SETTINGS.spriteBasePath + "/objects/Knight/idle/idle1.png";
        spriteFileName = enemyFileName;
      } else if (gameObject.tag() == TAG_EDITOR_GOAL) {
        clip = {70, 70, 98, 98};
        std::string goalDownFileName = SETTINGS.spriteBasePath + "/objects/Mage/Death/death5.png";
        spriteFileName = goalDownFileName;
      } else if (gameObject.tag() == TAG_EDITOR_COLLECTIBLE) {
        spriteFileName = SETTINGS.spriteBasePath + "/collectibles/coins/Gold/Gold_1.png";
        nullClip = true;
      } else if (gameObject.tag() == TAG_EDITOR_POWERUP) {
        spriteFileName = SETTINGS.spriteBasePath + "/collectibles/coins/Silver/Silver_1.png";
        nullClip = true;
      } else if (gameObject.tag() == TAG_EDITOR_BLOCK_1) {
        spriteFileName = SETTINGS.spriteBasePath + "/tiles/1.png";
        nullClip = true;
      } else if (gameObject.tag() == TAG_EDITOR_BLOCK_2 || gameObject.tag() == TAG_EDITOR_BLOCK) {
        spriteFileName = SETTINGS.spriteBasePath + "/tiles/2.png";
        nullClip = true;
      } else if (gameObject.tag() == TAG_EDITOR_BLOCK_3) {
        spriteFileName = SETTINGS.spriteBasePath + "/tiles/3.png";
        nullClip = true;
      } else if (gameObject.tag() == TAG_EDITOR_BLOCK_4) {
        spriteFileName = SETTINGS.spriteBasePath + "/tiles/4.png";
        nullClip = true;
      } else if (gameObject.tag() == TAG_EDITOR_BLOCK_5) {
        spriteFileName = SETTINGS.spriteBasePath + "/tiles/5.png";
        nullClip = true;
      } else if (gameObject.tag() == TAG_EDITOR_BLOCK_6) {
        spriteFileName = SETTINGS.spriteBasePath + "/tiles/6.png";
        nullClip = true;
      } else if (gameObject.tag() == TAG_EDITOR_EMPTY) {
        spriteFileName = SETTINGS.spriteBasePath + "/../" + "0.png";
        nullClip = true;
      } else if (gameObject.tag() == TAG_EDITOR_SAVE) {
        spriteFileName = SETTINGS.spriteBasePath + "/../" + "save.png";
        nullClip = true;
      } else if (gameObject.tag() == TAG_EDITOR_BREAK_BLOCK1) {
        spriteFileName = SETTINGS.spriteBasePath + "/brick1.bmp";
        nullClip = true;
      } else if (gameObject.tag() == TAG_EDITOR_BREAK_BLOCK2) {
        spriteFileName = SETTINGS.spriteBasePath + "/brick2.bmp";
        nullClip = true;
      } else if (gameObject.tag() == TAG_EDITOR_BREAK_BLOCK3) {
        spriteFileName = SETTINGS.spriteBasePath + "/brick3.bmp";
        nullClip = true;
      } else if (gameObject.tag() == TAG_EDITOR_BREAK_BALL) {
        spriteFileName = SETTINGS.spriteBasePath + "/ball.bmp";
        nullClip = true;
      } else if (gameObject.tag() == TAG_EDITOR_BREAK_PADDLE) {
        spriteFileName = SETTINGS.spriteBasePath + "/paddle.bmp";
        nullClip = true;
      } else if (gameObject.tag() == TAG_EDITOR_DOOR) {
        spriteFileName = SETTINGS.spriteBasePath + "/tiles/door.png";
        nullClip = true;
      } else if (gameObject.tag() == TAG_EDITOR_KEY) {
        spriteFileName = SETTINGS.spriteBasePath + "/collectibles/Key/Key_1.png";
        nullClip = true;
      } else if (gameObject.tag() == TAG_EDITOR_HEALTH) {
        spriteFileName = SETTINGS.spriteBasePath + "/collectibles/Health/Health_1.png";
        nullClip = true;
      } else if (gameObject.tag() == TAG_EDITOR_MAGE) {
        spriteFileName = SETTINGS.spriteBasePath + "/objects/Mage/Idle/idle1.png";
        // nullClip = true;
      } else if (gameObject.tag() == TAG_EDITOR_PLAYER_1) {
        spriteFileName = SETTINGS.spriteBasePath + "/objects/Warrior/Idle/idle1.png";
        nullClip = true;
      } else if (gameObject.tag() == TAG_EDITOR_PASSIVE_ENEMY) {
        spriteFileName = SETTINGS.spriteBasePath + "/objects/Rock/idle/idle1.png";
        nullClip = true;
      } else if (gameObject.tag() == TAG_EDITOR_PASSIVE_ENEMY) {
        spriteFileName = SETTINGS.spriteBasePath + "/objects/Rock/idle/idle1.png";
        nullClip = true;
      } else if (gameObject.tag() == TAG_EDITOR_DETECTOR) {
        spriteFileName = SETTINGS.spriteBasePath + "/tiles/detector.png";
        nullClip = true;
      }

      if (nullClip) {
        SDL_RenderCopyEx(renderer, RESOURCE_MANAGER.getTexture(spriteFileName), NULL, &renderQuad, 0.0f, NULL, SDL_FLIP_NONE);
      } else {
        SDL_RenderCopyEx(renderer, RESOURCE_MANAGER.getTexture(spriteFileName), &clip, &renderQuad, 0.0f, NULL, SDL_FLIP_NONE);
      }
    }

    // check if mouse clicked in tool box area
    // SDL_Log("getSelectTag [%d], current [%d]", level.getSelectTag(), gameObject.tag());
    if (level.getSelectTag() >= TAG_EDITOR_EMPTY &&
        level.getSelectTag() == gameObject.tag()) {
      bool drawRact = false;
      if (gameObject.tag() == TAG_EDITOR_LEVEL) {
        /* level buttons */
        // drawRact = gameObject.isColliding(level.getShiftedMouseX(), level.getShiftedMouseY());
      } else {
        drawRact = true;
      }
      if (drawRact) {
        SDL_Rect drawRect = {int(gameObject.x()), int(gameObject.y()), SETTINGS.cellWidth, SETTINGS.cellHeight};
        SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, 0xff);
        SDL_RenderDrawRect(renderer, &drawRect);
      }
    }

    std::stringstream mTopText;
    int hintY = SETTINGS.screenHeight - 60;
    mTopText << "Select an entity in the toolbox then click on screen to add it to the level or hover a space and press a Hot Key to edit";
    TextTexture* mTextTexture = RESOURCE_MANAGER.getTextTexture(mFont, mTopText.str().c_str(), {255, 255, 0, 255});
    mTextTexture->render(renderer, 15, hintY);

    std::stringstream mBottomText;
    if (SETTINGS.gameType == "breakout") {
      mBottomText << "Hot Keys: R = remove, Z = undo, Y = redo";
    } else {
      mBottomText << "Hot Keys: R = remove, Z = undo, Y = redo, P = player, C = collecitble, I = powerup, G = goal, A/S/D = terrain";
    }
    mTextTexture = RESOURCE_MANAGER.getTextTexture(mFont, mBottomText.str().c_str(), {255, 255, 0, 255});
    hintY += 30;
    mTextTexture->render(renderer, 15, hintY);

    std::stringstream mSavingText;
    SDL_Color textColor_ = {255, 100, 0, 255};
    if (!level.isSaved()) {
      mSavingText << "Level not Saved ...";
    } else {
      mSavingText << "Level Saved!";
      textColor_ = {0, 255, 0, 255};
    }
    mTextTexture = RESOURCE_MANAGER.getTextTexture(mFont, mSavingText.str().c_str(), textColor_);
    int boxY = SETTINGS.getFixedRowY(WORLD_MANAGER.row());
    mTextTexture->render(renderer, level.w() - mTextTexture->mWidth - 15, boxY + 15);
  }

 private:
  int mBoxX, mBoxY;
  int mBoxW, mBoxH;
  int mBorderSize;
};

#endif  // EDITOR_TOOL_BOX_RENDER_HPP