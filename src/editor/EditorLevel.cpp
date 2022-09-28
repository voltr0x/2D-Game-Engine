#include "EditorLevel.hpp"
#include "../Enemy.hpp"
#include "../MapCell.hpp"
#include "../MapObjects.hpp"
#include "../Player.hpp"
#include "../breakout/BreakoutLevel.hpp"
#include "../platformer/PlatFormerLevel.hpp"
#include "EditorObject.hpp"
#include "EditorToolBox.hpp"

EditorLevel::EditorLevel()
    : Level(SETTINGS.screenWidth, SETTINGS.screenHeight) {
}

void EditorLevel::initialize() {
  mEditorLevel = std::make_shared<PlatFormerLevel>();

  std::string mAppName = SETTINGS.appName + " [Level Editor]";
  setTitle(mAppName);
  setState(STATE_EDITOR);

  addObject(std::make_shared<MapGrid>(*mEditorLevel, SETTINGS.cellWidth, SETTINGS.cellHeight));
  addObject(std::make_shared<Displayer>(*mEditorLevel));
  addObject(std::make_shared<EditorToolBox>(*mEditorLevel, TAG_EDITOR_TOOL_BOX));

  // level choose buttons
  int totalLevels = WORLD_MANAGER.getLevelList().size();
  int offset = (WORLD_MANAGER.col() - totalLevels) / 2;
  int lbHeight = 10;
  // int lbHeight = b ? 24 : 10;
  for (size_t i = 0; i < (size_t)totalLevels; i++) {
    addObject(std::make_shared<EditorLevelButton>(*mEditorLevel, i + offset, lbHeight, TAG_EDITOR_LEVEL, i));
  }

  loadMap();
  
}

void EditorLevel::loadMap() {
  addObject(std::make_shared<EditorObject>(*mEditorLevel, 1, 11, TAG_EDITOR_PLAYER));
  addObject(std::make_shared<EditorObject>(*mEditorLevel, 3, 11, TAG_EDITOR_ENEMY));
  // addObject(std::make_shared<EditorObject>(*this, 5, 11, TAG_EDITOR_COLLECTIBLE));
  // addObject(std::make_shared<EditorObject>(*this, 7, 11, TAG_EDITOR_POWERUP));
  // addObject(std::make_shared<EditorObject>(*this, 9, 11, TAG_EDITOR_GOAL));
  // addObject(std::make_shared<EditorObject>(*this, 11, 11, TAG_EDITOR_BLOCK_1));
  // addObject(std::make_shared<EditorObject>(*this, 12, 11, TAG_EDITOR_BLOCK_2));
  // addObject(std::make_shared<EditorObject>(*this, 13, 11, TAG_EDITOR_BLOCK_3));
  // addObject(std::make_shared<EditorObject>(*this, 11, 12, TAG_EDITOR_BLOCK_4));
  // addObject(std::make_shared<EditorObject>(*this, 12, 12, TAG_EDITOR_BLOCK_5));
  // addObject(std::make_shared<EditorObject>(*this, 13, 12, TAG_EDITOR_BLOCK_6));
  // addObject(std::make_shared<EditorObject>(*this, 15, 11, TAG_EDITOR_EMPTY));
  // addObject(std::make_shared<EditorObject>(*this, 18, 11, TAG_EDITOR_SAVE));

  // mEditorLevel->initialize();
  // for (auto& obj : mEditorLevel->getAllObjects()) {
  //   addObject(obj);
  // }
};

void EditorLevel::addObjectToLevel(float x, float y, char objectType) {
}
