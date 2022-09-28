/**
 * @file main-platformer.cpp
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

#include "../base/SDLGraphicsProgram.hpp"
#include "CustomLevel.hpp"
#include "MapCell.hpp"
#include "MapObjects.hpp"
#include "Setup.hpp"

/**
 * Main function for the custom game. Loades the custom levels into SDLGraphicsProgram and runs the loop.
 */
int main(int argc, char* argv[]) {
  loadSettings(CUSTOM_SETTINGS_FILE_NAME);

  std::cout << "Started game: " << SETTINGS.gameType << std::endl;

  // TODO build map
  WORLD_MANAGER.init();
  // update screen size moved to WORLD_MANAGER.init()

  SDLGraphicsProgram mySDLGraphicsProgram(std::make_shared<CustomLevel>());
  mySDLGraphicsProgram.loop();

  Mix_Pause(BGM);
  return 0;
}
