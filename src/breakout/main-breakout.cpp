/**
 * @file main.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-03-04
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <cctype>
#include <iostream>
#include <memory>

#include "MapCell.hpp"
#include "MapObjects.hpp"
#include "Setup.hpp"
#include "base/Level.hpp"
#include "BreakoutLevel.hpp"
#include "base/SDLGraphicsProgram.hpp"
#include "BreakoutObjects.hpp"

int main(int argc, char* argv[]) {
  loadSettings(BREAKOUT_SETTINGS_FILE_NAME);

  WORLD_MANAGER.init();
  // update screen size moved to WORLD_MANAGER.init()
  // SETTINGS.screenHeight = 720;
  // SETTINGS.screenWidthd = 1280;

  SDLGraphicsProgram mySDLGraphicsProgram(std::make_shared<BreakoutLevel>());
  mySDLGraphicsProgram.loop();

  Mix_Pause(BGM);
  return 0;
}
