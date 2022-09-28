#include "Editor.hpp"
#include "../Enemy.hpp"
#include "../MapCell.hpp"
#include "../MapObjects.hpp"
#include "../Player.hpp"
#include "../base/FpsManager.hpp"

Editor::Editor(std::shared_ptr<Level> level)
    : SDLGraphicsProgram(level) {
  editing = true;
  mLevel->loadMap();
  // mLevel->initialize();
}

void Editor::edit() {
  SDL_Event e;

  // Fps cap
  FpsManager fpsManager;

  while (mLevel->state() >= 0) {
    InputManager::getInstance().resetForFrame();

    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        mLevel->setState(-1);
      }
      InputManager::getInstance().handleEvent(e);
    }
    mLevel->updateEditor();
    render();

    // update fps Reduce framerate
    SDL_Delay(fpsManager.delay());
    mLevel->setFps(fpsManager.avgFps());
  }
}
