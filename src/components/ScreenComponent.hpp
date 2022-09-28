#if !defined(SCREEN_COMPONENT_HPP)
#define SCREEN_COMPONENT_HPP

#include <iomanip>
#include <iostream>
#include "Globals.hpp"
#include "base/DisplayComponent.hpp"

class ScreenComponent : public DisplayComponent {
 public:
  inline ScreenComponent(GameObject& gameObject)
      : DisplayComponent(gameObject) {
  }

  inline virtual void display(Level& level, SDL_Renderer* renderer) override {
    const GameObject& gameObject = getGameObject();

    TTF_Font* mFont = RESOURCE_MANAGER.getFont(FONT_NORMAL, 24);
    TTF_Font* mFontL = RESOURCE_MANAGER.getFont(FONT_NORMAL, 32);
    TTF_Font* mFontMenu = RESOURCE_MANAGER.getFont(FONT_MENU, 20);

    int _y = gameObject.y() + 15;
    std::stringstream mText;
    mText << "FPS: " << std::fixed << std::setprecision(2) << level.fps();
    TextTexture* mTextTexture = RESOURCE_MANAGER.getTextTexture(mFont, mText.str().c_str(), {255, 255, 0, 255});
    mTextTexture->render(renderer, 15, _y);

    // add current level info
    mText.str("");
    mText << "Level " << level.getLevelId() << " / " << WORLD_MANAGER.getLevelCount();
    mTextTexture = RESOURCE_MANAGER.getTextTexture(mFont, mText.str().c_str(), {255, 255, 0, 255});
    mTextTexture->render(renderer, level.w() - mTextTexture->mWidth - 15, _y);

    if (level.getLives() >= 0) {
      mText.str("");
      mText << "Lives: " << level.getLives();
      mTextTexture = RESOURCE_MANAGER.getTextTexture(mFont, mText.str().c_str(), {255, 255, 0, 255});
      _y += 25;
      mTextTexture->render(renderer, 15, _y);
    }

    mText.str("");
    mText << "Score: " << level.collection();
    mTextTexture = RESOURCE_MANAGER.getTextTexture(mFont, mText.str().c_str(), {255, 255, 0, 255});
    _y += 25;
    mTextTexture->render(renderer, 15, _y);

    // SDL_Log("ScreenComponent::display [state: %d]", level.state());

    if (level.state() == STATE_WIN) {
      // render background
      renderBackground(level, renderer);

      /* display wining screen */
      mFontL = RESOURCE_MANAGER.getFont(FONT_MENU, 32);
      if (level.getLevelId() < WORLD_MANAGER.getLevelCount()) {
        mText.str("Nice! You saved her!");
      } else {
        mText.str("Great! You got her number!");
      }

      mTextTexture = RESOURCE_MANAGER.getTextTexture(mFontL, mText.str().c_str(), {200, 200, 0, 255});
      SDL_Point sizeT = mTextTexture->size();

      int _y = level.h() / 3 - sizeT.y;
      mTextTexture->render(renderer, (level.w() - sizeT.x) / 2, _y);

      mText.str("Press [R] to Restart!");
      mTextTexture = RESOURCE_MANAGER.getTextTexture(mFontMenu, mText.str().c_str(), {200, 200, 200, 255});
      sizeT = mTextTexture->size();
      _y += 100;
      mTextTexture->render(renderer, (level.w() - sizeT.x) / 2, _y);

      if (level.getLevelId() < WORLD_MANAGER.getLevelCount()) {
        mText.str("Press [N] to go to next level!");
        mTextTexture = RESOURCE_MANAGER.getTextTexture(mFontMenu, mText.str().c_str(), {200, 200, 200, 255});
        sizeT = mTextTexture->size();
        _y += 200;
        mTextTexture->render(renderer, (level.w() - sizeT.x) / 2, _y);
      }
    } else if (level.state() == STATE_PAUSE) {
      // TODO pause screen need capsulation for duplicate code
      // render background
      renderBackground(level, renderer);
      /* display title*/
      TTF_Font* mFontLogo = RESOURCE_MANAGER.getFont(FONT_MENU, 48);
      mText.str("");
      mText << level.title();
      mTextTexture = RESOURCE_MANAGER.getTextTexture(mFontLogo, mText.str().c_str(), {255, 255, 255, 255});
      SDL_Point sizeT = mTextTexture->size();

      int _y = level.h() / 3 - sizeT.y;
      mTextTexture->render(renderer, (level.w() - sizeT.x) / 2, _y);

      mText.str("Press [P] to resume ...");
      mTextTexture = RESOURCE_MANAGER.getTextTexture(mFontMenu, mText.str().c_str(), {200, 200, 0, 255});
      sizeT = mTextTexture->size();
      _y += 100;
      mTextTexture->render(renderer, (level.w() - sizeT.x) / 2, _y);
    } else if (level.state() == STATE_START) {
      // start screen
      // render background
      renderBackground(level, renderer);

      /* display title*/
      TTF_Font* mFontLogo = RESOURCE_MANAGER.getFont(FONT_MENU, 48);
      mText.str("");
      mText << level.title();
      mTextTexture = RESOURCE_MANAGER.getTextTexture(mFontLogo, mText.str().c_str(), {255, 255, 255, 255});
      SDL_Point sizeT = mTextTexture->size();

      int _y = level.h() / 3 - sizeT.y;
      mTextTexture->render(renderer, (level.w() - sizeT.x) / 2, _y);

      // menu
      std::string l = "LEVEL " + std::to_string(WORLD_MANAGER.getLevel());
      mText.str(l);
      mTextTexture = RESOURCE_MANAGER.getTextTexture(mFontMenu, mText.str().c_str(), {200, 200, 200, 255});
      sizeT = mTextTexture->size();
      _y += 100;
      mTextTexture->render(renderer, (level.w() - sizeT.x) / 2, _y);

      mText.str("Press [Space] to start ...");
      mTextTexture = RESOURCE_MANAGER.getTextTexture(mFontMenu, mText.str().c_str(), {200, 200, 0, 255});
      sizeT = mTextTexture->size();
      _y += 100;
      mTextTexture->render(renderer, (level.w() - sizeT.x) / 2, _y);
    } else if (level.state() == STATE_KILLED) {
      // TODO need capsulation
      // missed/killed
      // render background
      renderBackground(level, renderer);
      /* display wining screen */
      mFontL = RESOURCE_MANAGER.getFont(FONT_MENU, 32);
      mText.str("You missed!");
      mTextTexture = RESOURCE_MANAGER.getTextTexture(mFontL, mText.str().c_str(), {200, 200, 0, 255});
      SDL_Point sizeT = mTextTexture->size();

      int _y = level.h() / 3 - sizeT.y;
      mTextTexture->render(renderer, (level.w() - sizeT.x) / 2, _y);

      mText.str("Press [Space] to continue ...");
      mTextTexture = RESOURCE_MANAGER.getTextTexture(mFontMenu, mText.str().c_str(), {200, 200, 200, 255});
      sizeT = mTextTexture->size();
      _y += 100;
      mTextTexture->render(renderer, (level.w() - sizeT.x) / 2, _y);
    } else if (level.state() == STATE_LOSE) {
      // render background
      renderBackground(level, renderer);

      /* display wining screen */
      mFontL = RESOURCE_MANAGER.getFont(FONT_MENU, 32);
      mText.str("You lose :(");
      mTextTexture = RESOURCE_MANAGER.getTextTexture(mFontL, mText.str().c_str(), {200, 200, 0, 255});
      SDL_Point sizeT = mTextTexture->size();

      int _y = level.h() / 3 - sizeT.y;
      mTextTexture->render(renderer, (level.w() - sizeT.x) / 2, _y);

      mText.str("Press [R] to Restart!");
      mTextTexture = RESOURCE_MANAGER.getTextTexture(mFontMenu, mText.str().c_str(), {200, 200, 200, 255});
      sizeT = mTextTexture->size();
      _y += 100;
      mTextTexture->render(renderer, (level.w() - sizeT.x) / 2, _y);
    } else if (level.state() == STATE_EDITOR_LEVEL) {
      // SDL_Point sizeT = mTextTexture->size();
      // std::vector<std::string> numLevel = WORLD_MANAGER.getLevelList();
      // renderBackground(level, renderer);
      // int _y = level.h() / 4 - sizeT.y;
      // mTextTexture->render(renderer, (level.w() - sizeT.x) / 2, _y);

      // mText.str("");
      // mText << "Welcome to Level Editor";
      // mTextTexture = RESOURCE_MANAGER.getTextTexture(mFontMenu, mText.str().c_str(), {200, 200, 200, 255});
      // sizeT = mTextTexture->size();
      // mTextTexture->render(renderer, (level.w() - sizeT.x) / 2, _y);
      // std::string leveltext = "Choose a level from 1 to " + std::to_string(numLevel.size());
      // mText.str(leveltext);
      // mTextTexture = RESOURCE_MANAGER.getTextTexture(mFontMenu, mText.str().c_str(), {200, 200, 200, 255});
      // sizeT = mTextTexture->size();
      // _y += 50;
      // mTextTexture->render(renderer, (level.w() - sizeT.x) / 2, _y);

      // mTextTexture->render(renderer, (level.w() - sizeT.x) / 2, _y);
    }
    if (level.state() != STATE_EDITOR_LEVEL) {
      // instructions
      std::stringstream mBottomText;
      
      if(SETTINGS.gameType == "custom")
      {
        mBottomText << "Hot Keys: P = Pause, R = Reset, N = Next Level, O = Toggle Random Level Generation, Q/ESC = Quit, Up = Jump, Left, Right to move.";
      }
      else
      {
        mBottomText << "Hot Keys: P = Pause, R = Reset, N = Next Level, Q/ESC = Quit, Up = Jump, Left, Right to move.";
      }
      mTextTexture = RESOURCE_MANAGER.getTextTexture(mFont, mBottomText.str().c_str(), {255, 255, 0, 255});
      mTextTexture->render(renderer, 15, level.h() - mTextTexture->mHeight - 0);
    }
  }

  inline void renderBackground(Level& level, SDL_Renderer* renderer) {
    // render background
    SDL_Rect fillRect = {0, 0, level.w(), level.h()};
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(renderer, &fillRect);
  }
};

#endif  // SCREEN_COMPONENT_HPP
