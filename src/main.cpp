#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <cctype>
#include <iostream>
#include <memory>

#include "Globals.hpp"
#include "MapCell.hpp"
#include "MapObjects.hpp"
#include "Setup.hpp"
#include "base/Level.hpp"

#include "base/SDLGraphicsProgram.hpp"

int STATUS_CODE = 0;

class LaunchDisplayer : public GameObject {
 public:  // TODO add more TAGs for sound, display component
  LaunchDisplayer(Level& level)
      : GameObject(level, 0, 0, 0, 0, TAG_IGNORE) {
    setDisplayCompenent(std::make_shared<LuanchScreenComponent>(*this));
  }

  class LuanchScreenComponent : public DisplayComponent {
   public:
    inline LuanchScreenComponent(GameObject& gameObject)
        : DisplayComponent(gameObject) {
    }

    inline virtual void display(Level& level, SDL_Renderer* renderer) override {
      TTF_Font* mFont = RESOURCE_MANAGER.getFont(FONT_NORMAL, 24);
      int _y = 15;
      std::stringstream mText;
      mText << "FPS: " << std::fixed << std::setprecision(2) << level.fps();
      TextTexture* mTextTexture = RESOURCE_MANAGER.getTextTexture(mFont, mText.str().c_str(), {255, 255, 0, 255});
      mTextTexture->render(renderer, 15, _y);

      // team name
      mText.str("");
      mText << "CS5850 Custom Project";
      mTextTexture = RESOURCE_MANAGER.getTextTexture(mFont, mText.str().c_str(), {255, 255, 0, 255});
      _y = 100;
      mTextTexture->render(renderer, (SETTINGS.screenWidth - mTextTexture->mWidth) / 2, _y);

      TTF_Font* mFontL = RESOURCE_MANAGER.getFont(FONT_NORMAL, 42);

      mText.str("");
      mText << "ASDY Custom";
      mTextTexture = RESOURCE_MANAGER.getTextTexture(mFontL, mText.str().c_str(), {255, 255, 0, 255});
      _y += 50;
      mTextTexture->render(renderer, (SETTINGS.screenWidth - mTextTexture->mWidth) / 2, _y);
    }
  };
};

class LaunchButton : public GameObject {
 public:
  LaunchButton(Level& level, int x, int y, int tag)
      : GameObject(level, x, y, 200, 50, tag) {
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
      SDL_Rect renderQuad = {int(gameObject.x()),
                             int(gameObject.y()),
                             int(gameObject.w()),
                             int(gameObject.h())};
      //   SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, 0x99);
      //   SDL_RenderDrawRect(renderer, &drawRect);

      //   SDL_SetRenderDrawColor(renderer, 0xff, 0x22, 0x22, 0xFF);
      //   SDL_RenderFillRect(renderer, &renderQuad);

      std::string spriteFileName = "sprites/btn/button1.png";
      SDL_RenderCopyEx(renderer, RESOURCE_MANAGER.getTexture(spriteFileName), NULL, &renderQuad, 0.0f, NULL, SDL_FLIP_NONE);
      // render text
      TTF_Font* mFont = RESOURCE_MANAGER.getFont(FONT_NORMAL, 28);
      std::string binName = "Undefined";
      if (gameObject.tag() == TAG_BUTTON_BREAKOUT) {
        binName = "Breakout";
      } else if (gameObject.tag() == TAG_BUTTON_BREAKOUT_EDITOR) {
        binName = "Breakout Editor";
      } else if (gameObject.tag() == TAG_BUTTON_PLATFORMER) {
        binName = "Platformer";
      } else if (gameObject.tag() == TAG_BUTTON_PLATFORMER_EDITOR) {
        binName = "Platformer Editor";
      } else if (gameObject.tag() == TAG_BUTTON_CUSTOM) {
        binName = "Custom";
      } else if (gameObject.tag() == TAG_BUTTON_CUSTOM_EDITOR) {
        binName = "Custom Editor";
      }
      TextTexture* mTextTexture = RESOURCE_MANAGER.getTextTexture(mFont, binName.c_str(), {0, 0, 0, 255});
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
        if (gameObject.tag() == TAG_BUTTON_BREAKOUT) {
          binName = "breakout/main-breakout";
          argv[1] = NULL;
        } else if (gameObject.tag() == TAG_BUTTON_PLATFORMER) {
          binName = "platformer/main-platformer";
          argv[1] = NULL;
        } else if (gameObject.tag() == TAG_BUTTON_CUSTOM) {
          binName = "custom/main-custom";
          argv[1] = NULL;
        } else if (gameObject.tag() == TAG_BUTTON_BREAKOUT_EDITOR) {
          binName = "editor/main-editor";
          std::string argv1 = "--game";
          std::string argv2 = "breakout";
          argv[1] = strcpy(new char[argv1.length() + 1], argv1.c_str());
          argv[2] = strcpy(new char[argv2.length() + 1], argv2.c_str());
          argv[3] = NULL;
        } else if (gameObject.tag() == TAG_BUTTON_PLATFORMER_EDITOR) {
          binName = "editor/main-editor";
          std::string argv1 = "--game";
          std::string argv2 = "platformer";
          argv[1] = strcpy(new char[argv1.length() + 1], argv1.c_str());
          argv[2] = strcpy(new char[argv2.length() + 1], argv2.c_str());
          argv[3] = NULL;
        } else if (gameObject.tag() == TAG_BUTTON_CUSTOM_EDITOR) {
          binName = "editor/main-editor";
          std::string argv1 = "--game";
          std::string argv2 = "custom";
          argv[1] = strcpy(new char[argv1.length() + 1], argv1.c_str());
          argv[2] = strcpy(new char[argv2.length() + 1], argv2.c_str());
          argv[3] = NULL;
        }

        if (binName != "") {
          // system(getBinName(binName).c_str());
          std::string binFile = "bin/" + binName;
          argv[0] = strcpy(new char[binFile.length() + 1], binFile.c_str());
          STATUS_CODE = execvp(binFile.c_str(), argv);
          if (STATUS_CODE == -1) {
            printf("Process did not terminate correctly\n");
          }
          printf("This line will not be printed if execvp() runs correctly\n");
        } else {
          SDL_Log("No executable on this button!");
        }
      }
    };
  };
};

class LaunchLevel : public Level {
 public:
  LaunchLevel()
      : Level(SETTINGS.screenWidth, SETTINGS.screenHeight){

        };

  void initialize() override {
    setTitle(SETTINGS.appName);
    addObject(std::make_shared<MapGrid>(*this, SETTINGS.cellWidth, SETTINGS.cellHeight));
    addObject(std::make_shared<LaunchDisplayer>(*this));
    addObject(std::make_shared<LaunchButton>(*this, 100, 300, TAG_BUTTON_BREAKOUT));
    addObject(std::make_shared<LaunchButton>(*this, 100, 400, TAG_BUTTON_BREAKOUT_EDITOR));
    addObject(std::make_shared<LaunchButton>(*this, 400, 300, TAG_BUTTON_PLATFORMER));
    addObject(std::make_shared<LaunchButton>(*this, 400, 400, TAG_BUTTON_PLATFORMER_EDITOR));
    addObject(std::make_shared<LaunchButton>(*this, 700, 300, TAG_BUTTON_CUSTOM));
    addObject(std::make_shared<LaunchButton>(*this, 700, 400, TAG_BUTTON_CUSTOM_EDITOR));
  };
  void loadMap() override{};

  void revive() override{};
};

int main(int argc, char* argv[]) {
  loadSettings("configs/launch_settings.ini");

  WORLD_MANAGER.init();
  SETTINGS.appName = "Game Luancher";
  SETTINGS.screenHeight = 9 * SETTINGS.cellHeight;
  SETTINGS.screenWidth = 16 * SETTINGS.cellWidth;
  // SETTINGS.screenHeight = 720;
  // SETTINGS.screenWidth = 1280;

  SDLGraphicsProgram mySDLGraphicsProgram(std::make_shared<LaunchLevel>());
  mySDLGraphicsProgram.loop();

  return 0;
}
