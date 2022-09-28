#include <cctype>
#include <iostream>
#include <memory>

#include "../Enemy.hpp"
#include "../MapCell.hpp"
#include "../MapObjects.hpp"
#include "../Player.hpp"
#include "../Setup.hpp"
#include "../TopBar.hpp"
#include "../base/Level.hpp"
#include "../base/SDLGraphicsProgram.hpp"
#include "../breakout/BreakoutLevel.hpp"
#include "../custom/CustomLevel.hpp"
#include "../platformer/PlatFormerLevel.hpp"
#include "Editor.hpp"
#include "EditorInput.hpp"
#include "EditorLevel.hpp"
#include "EditorObject.hpp"
#include "EditorToolBox.hpp"

int main(int argc, char* argv[]) {
  std::string currGame = "platformer";

  if (argc > 2) {
    if (std::string(argv[1]) == "--game") {
      currGame = std::string(argv[2]);
    }
  } else {
    std::cerr << "Usage: " << argv[0] << " --game {custom, breakout or platformer}" << std::endl;
    // return 1;
  }

  // int editorCol = 0;
  if (currGame == "breakout") {
    loadSettings(BREAKOUT_SETTINGS_FILE_NAME);
  } else if (currGame == "platformer") {
    loadSettings(PLATFORMER_SETTINGS_FILE_NAME);
  } else if (currGame == "custom") {
    loadSettings(CUSTOM_SETTINGS_FILE_NAME);
    // TODO add this to settings
    // editorCol = SETTINGS.editorCols;
  }

  WORLD_MANAGER.init();
  // std::vector<std::vector<std::string>> mMap = WORLD_MANAGER.mapVector();
  // update screen size
  SETTINGS.screenWidth = (WORLD_MANAGER.col() + SETTINGS.mapOffsetCol) * SETTINGS.cellWidth;
  SETTINGS.screenHeight = (WORLD_MANAGER.row() + SETTINGS.editorRows) * SETTINGS.cellHeight;
  if (SETTINGS.showTopBar) {
    SETTINGS.screenHeight += SETTINGS.topBarHeight;
  }

  std::shared_ptr<Level> level;
  if (currGame == "breakout") {
    level = std::make_shared<BreakoutLevel>();
  } else if (currGame == "platformer") {
    level = std::make_shared<PlatFormerLevel>();
  } else if (currGame == "custom") {
    level = std::make_shared<CustomLevel>();
  }
  std::string appName = SETTINGS.appName + " [Level Editor]";
  level->setTitle(appName);
  level->addObject(std::make_shared<MapGrid>(*level, SETTINGS.cellWidth, SETTINGS.cellHeight));
  level->addObject(std::make_shared<EditorInput>(*level));
  // level->setState(STATE_EDITOR_LEVEL);
  level->setState(STATE_EDITOR);
  level->addObject(std::make_shared<Displayer>(*level));
  level->addObject(std::make_shared<EditorToolBox>(*level, TAG_EDITOR_TOOL_BOX));

  // level->loadMap();
  //  add editor box
  if (currGame == "breakout") {
    level->addObject(std::make_shared<EditorObject>(*level, 0, 25, TAG_EDITOR_BREAK_BLOCK1));
    level->addObject(std::make_shared<EditorObject>(*level, 2, 25, TAG_EDITOR_BREAK_BLOCK2));
    level->addObject(std::make_shared<EditorObject>(*level, 4, 25, TAG_EDITOR_BREAK_BLOCK3));
    level->addObject(std::make_shared<EditorObject>(*level, 8, 25, TAG_EDITOR_BREAK_PADDLE));
    level->addObject(std::make_shared<EditorObject>(*level, 10, 25, TAG_EDITOR_BREAK_BALL));
    level->addObject(std::make_shared<EditorObject>(*level, 11, 25, TAG_EDITOR_EMPTY));
    level->addObject(std::make_shared<EditorObject>(*level, 12, 25, TAG_EDITOR_SAVE));
  } else if (currGame == "platformer") {
    level->addObject(std::make_shared<EditorObject>(*level, 1, 11, TAG_EDITOR_PLAYER));
    level->addObject(std::make_shared<EditorObject>(*level, 3, 11, TAG_EDITOR_ENEMY));
    level->addObject(std::make_shared<EditorObject>(*level, 5, 11, TAG_EDITOR_COLLECTIBLE));
    level->addObject(std::make_shared<EditorObject>(*level, 7, 11, TAG_EDITOR_POWERUP));
    level->addObject(std::make_shared<EditorObject>(*level, 9, 11, TAG_EDITOR_GOAL));
    level->addObject(std::make_shared<EditorObject>(*level, 11, 11, TAG_EDITOR_BLOCK_1));
    level->addObject(std::make_shared<EditorObject>(*level, 12, 11, TAG_EDITOR_BLOCK_2));
    level->addObject(std::make_shared<EditorObject>(*level, 13, 11, TAG_EDITOR_BLOCK_3));
    level->addObject(std::make_shared<EditorObject>(*level, 11, 12, TAG_EDITOR_BLOCK_4));
    level->addObject(std::make_shared<EditorObject>(*level, 12, 12, TAG_EDITOR_BLOCK_5));
    level->addObject(std::make_shared<EditorObject>(*level, 13, 12, TAG_EDITOR_BLOCK_6));
    level->addObject(std::make_shared<EditorObject>(*level, 15, 11, TAG_EDITOR_EMPTY));
    level->addObject(std::make_shared<EditorObject>(*level, 18, 11, TAG_EDITOR_SAVE));
  } else if (currGame == "custom") {
    level->addObject(std::make_shared<EditorObject>(*level, 1, 11, TAG_EDITOR_PLAYER_1));
    level->addObject(std::make_shared<EditorObject>(*level, 3, 11, TAG_EDITOR_ENEMY));
    level->addObject(std::make_shared<EditorObject>(*level, 5, 11, TAG_EDITOR_KEY));
    level->addObject(std::make_shared<EditorObject>(*level, 9, 11, TAG_EDITOR_MAGE));
    // level->addObject(std::make_shared<EditorObject>(*level, 9, 11, TAG_EDITOR_GOAL));
    level->addObject(std::make_shared<EditorObject>(*level, 11, 11, TAG_EDITOR_BLOCK_1));
    level->addObject(std::make_shared<EditorObject>(*level, 13, 11, TAG_EDITOR_DOOR));
    // level->addObject(std::make_shared<EditorObject>(*level, 12, 11, TAG_EDITOR_BLOCK_2));
    // level->addObject(std::make_shared<EditorObject>(*level, 13, 11, TAG_EDITOR_BLOCK_3));
    // level->addObject(std::make_shared<EditorObject>(*level, 11, 12, TAG_EDITOR_BLOCK_4));
    // level->addObject(std::make_shared<EditorObject>(*level, 12, 12, TAG_EDITOR_BLOCK_5));
    // level->addObject(std::make_shared<EditorObject>(*level, 13, 12, TAG_EDITOR_BLOCK_6));
    level->addObject(std::make_shared<EditorObject>(*level, 15, 11, TAG_EDITOR_EMPTY));
    level->addObject(std::make_shared<EditorObject>(*level, 18, 11, TAG_EDITOR_SAVE));
  }
  // level choose buttons
  int totalLevels = WORLD_MANAGER.getLevelList().size();
  int offset = (WORLD_MANAGER.col() - totalLevels) / 2;
  int lbHeight = currGame == "breakout" ? 24 : 10;
  for (size_t i = 0; i < (size_t)totalLevels; i++) {
    level->addObject(std::make_shared<EditorLevelButton>(*level, i + offset, lbHeight, TAG_EDITOR_LEVEL, i));
  }

  // SDLGraphicsProgram mySDLGraphicsProgram(std::make_shared<EditorLevel>());
  // mySDLGraphicsProgram.loop();

  Editor editor(level);
  editor.edit();

  return 0;
}
