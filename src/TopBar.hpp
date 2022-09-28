#if !defined(TOP_BAR_HPP)
#define TOP_BAR_HPP

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include "Globals.hpp"
#include "base/GameObject.hpp"
#include "base/PhysicsComponent.hpp"

class TopBarButton : public GameObject {
 public:
  TopBarButton(Level& level, int x, int y, int tag)
      : GameObject(level, x, y, 100, 32, tag) {
    setRenderCompenent(std::make_shared<ButtonRenderComponent>(*this));
    addGenericCompenent(std::make_shared<ButtonClickComponent>(*this));
  }

  class ButtonRenderComponent : public RenderComponent {
   public:
    ButtonRenderComponent(GameObject& gameObject)
        : RenderComponent(gameObject) {
    }

    inline virtual void render(SDL_Renderer* renderer) const override {
      const GameObject& gameObject = getGameObject();
      const Level& level = gameObject.getLevel();
      SDL_Rect renderQuad = {int(gameObject.x()),
                             int(gameObject.y()),
                             int(gameObject.w()),
                             int(gameObject.h())};

      SDL_SetRenderDrawColor(renderer, 0x24, 0x29, 0x2f, 0xFF);
      SDL_RenderFillRect(renderer, &renderQuad);

      // render text
      TTF_Font* mFont = RESOURCE_MANAGER.getFont(FONT_NORMAL, 16);
      std::string binName = "";
      if (gameObject.tag() == TAG_TB_LAUNCH || gameObject.tag() == TAG_BUTTON) {
        binName = "Launcher";
      } else if (gameObject.tag() == TAG_TB_BREAKOUT_EDITOR ||
                 gameObject.tag() == TAG_TB_PLATFORMER_EDITOR ||
                 gameObject.tag() == TAG_TB_CUSTOM_EDITOR) {
        binName = "Level Editor";
        if (level.state() == STATE_EDITOR) {
          /* go to game play */
          binName = "Game Play";
        }
      }
      TextTexture* mTextTexture = RESOURCE_MANAGER.getTextTexture(mFont, binName.c_str(), {0xff, 0xff, 0xff, 255});
      int mX = (renderQuad.w - mTextTexture->mWidth) / 2;
      int mY = (renderQuad.h - mTextTexture->mHeight) / 2;
      mTextTexture->render(renderer, renderQuad.x + mX, renderQuad.y + mY);
    }
  };

  class ButtonClickComponent : public GenericComponent {
   private:
    /* data */
    int mMouseX{0}, mMouseY{0};

   public:
    ButtonClickComponent(GameObject& gameObject)
        : GenericComponent(gameObject){};

    virtual void update(Level& level) override {
      bool mouseLeftClicked = INPUT_MANAGER.isMousePressed(SDL_BUTTON_LEFT);
      //   bool mouseRightClicked = INPUT_MANAGER.isMousePressed(SDL_BUTTON_RIGHT);

      SDL_GetMouseState(&mMouseX, &mMouseY);
      const GameObject& gameObject = getGameObject();
      if (mouseLeftClicked && gameObject.isColliding(mMouseX, mMouseY)) {
        // is clicked
        std::string binName = "";
        char* argv[4];
        if (gameObject.tag() == TAG_TB_LAUNCH || gameObject.tag() == TAG_BUTTON) {
          binName = "main";
          if (execvp(getBinName(binName).c_str(), NULL) == -1) {
            printf("Process did not terminate correctly\n");
          }
        } else if (gameObject.tag() == TAG_TB_BREAKOUT_EDITOR ||
                   gameObject.tag() == TAG_TB_PLATFORMER_EDITOR ||
                   gameObject.tag() == TAG_TB_CUSTOM_EDITOR) {
          if (level.state() == STATE_EDITOR) {
            /* go to game play */
            if (gameObject.tag() == TAG_TB_PLATFORMER_EDITOR) {
              binName = "platformer/main-platformer";
            } else if (gameObject.tag() == TAG_TB_CUSTOM_EDITOR) {
              binName = "custom/main-custom";
            } else {
              binName = "breakout/main-breakout";
            }
            if (execvp(getBinName(binName).c_str(), NULL) == -1) {
              printf("Process did not terminate correctly\n");
            }
          } else {
            binName = "editor/main-editor";
            std::string argv1 = "--game";
            std::string argv2 = "breakout";
            if (gameObject.tag() == TAG_TB_PLATFORMER_EDITOR) {
              argv2 = "platformer";
            } else if (gameObject.tag() == TAG_TB_CUSTOM_EDITOR) {
              argv2 = "custom";
            } else {
              argv2 = "breakout";
            }

            std::string binFile = "bin/" + binName;
            argv[0] = strcpy(new char[binFile.length() + 1], binFile.c_str());
            argv[1] = strcpy(new char[argv1.length() + 1], argv1.c_str());
            argv[2] = strcpy(new char[argv2.length() + 1], argv2.c_str());
            argv[3] = NULL;

            // execvp(getBinName(binName).c_str(), NULL) == -1
            if (execvp(binFile.c_str(), argv) == -1) {
              printf("Process did not terminate correctly\n");
            }
            //
          }
        }
      }
    };
  };
};

class TopBar : public GameObject {
 private:
  /* data */
 public:
  inline TopBar(Level& level)
      : GameObject(level, 0, 0, SETTINGS.screenWidth, SETTINGS.topBarHeight, TAG_GENERAL) {
    setRenderCompenent(std::make_shared<TopBarRenderComponent>(*this));
  }

  class TopBarRenderComponent : public RenderComponent {
   public:
    TopBarRenderComponent(GameObject& gameObject)
        : RenderComponent(gameObject){};

    inline virtual void render(SDL_Renderer* renderer) const override {
      const GameObject& gameObject = getGameObject();
      SDL_Rect drawRect = {int(gameObject.x()), int(gameObject.y()), int(gameObject.w()), int(gameObject.h())};
      SDL_SetRenderDrawColor(renderer, 0xaa, 0xff, 0xaa, 0xFF);
      SDL_RenderFillRect(renderer, &drawRect);
    };

   private:
    /* data */
  };
};

#endif  // TOP_BAR_HPP
