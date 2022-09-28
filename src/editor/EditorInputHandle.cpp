#include "EditorInputHandle.hpp"
#include <SDL.h>
#include "../Enemy.hpp"
#include "../Globals.hpp"
#include "../MapCell.hpp"
#include "../MapObjects.hpp"
#include "../Player.hpp"
#include "../breakout/BreakoutObjects.hpp"
#include "../custom/CustomObjects.hpp"
#include "base/InputManager.hpp"

#define INPUT_MANAGER (InputManager::getInstance())

std::string collectibleBasePath = SETTINGS.spriteBasePath + "/collectibles/coins/Gold";
std::string powerupBasePath = SETTINGS.spriteBasePath + "/collectibles/coins/Silver";

EditorInputHandle::EditorInputHandle(GameObject& gameObject)
    : GenericComponent(gameObject) {
}

void EditorInputHandle::update(Level& level) {
  bool quit = INPUT_MANAGER.isKeyPressed(SDLK_q) || INPUT_MANAGER.isKeyPressed(SDLK_ESCAPE);
  bool mouseLeftClicked = INPUT_MANAGER.isMousePressed(SDL_BUTTON_LEFT);
  bool mouseRightClicked = INPUT_MANAGER.isMousePressed(SDL_BUTTON_RIGHT);

  SDL_GetMouseState(&mMouseX, &mMouseY);
  mShiftedX = mMouseX / SETTINGS.cellWidth * SETTINGS.cellWidth;
  int fixedMouseY = mMouseY;
  if (SETTINGS.showTopBar) {
    fixedMouseY -= SETTINGS.topBarHeight;
  }
  mShiftedY = fixedMouseY / SETTINGS.cellHeight * SETTINGS.cellHeight;
  mIndexX = mShiftedX / SETTINGS.cellWidth;
  mIndexY = mShiftedY / SETTINGS.cellHeight;

  std::shared_ptr<GameObject> objectToAdd = nullptr;
  std::shared_ptr<GameObject> toRemove = nullptr;
  std::vector<std::shared_ptr<GameObject>> objectsStore;

  // if (level.state() == STATE_EDITOR_LEVEL && INPUT_MANAGER.isKeyPressed(SDLK_1)) {
  //   WORLD_MANAGER.setLevel(0);
  //   WORLD_MANAGER.loadCurrentLevel();
  //   level.loadMap();
  //   level.setState(STATE_EDITOR);
  // } else if (level.state() == STATE_EDITOR_LEVEL && INPUT_MANAGER.isKeyPressed(SDLK_2)) {
  //   WORLD_MANAGER.setLevel(1);
  //   WORLD_MANAGER.loadCurrentLevel();
  //   level.setState(STATE_EDITOR);
  //   level.loadMap();
  // } else if (level.state() == STATE_EDITOR_LEVEL && INPUT_MANAGER.isKeyPressed(SDLK_3)) {
  //   WORLD_MANAGER.setLevel(2);
  //   WORLD_MANAGER.loadCurrentLevel();
  //   level.setState(STATE_EDITOR);
  //   level.loadMap();
  // }
  if (quit) {
    level.setState(STATE_QUIT);
  }
  if (level.state() != STATE_EDITOR_LEVEL) {
    std::string levelChar = ".";
    int tagIndex_ = 0;

    if (mouseLeftClicked) {
      level.setShiftedMouseX(mShiftedX);
      level.setShiftedMouseY(mShiftedY);
      level.getCollisions(mMouseX, mMouseY, objectsStore);
      // level.setSelectTag(-1);
      for (std::shared_ptr<GameObject>& obj : objectsStore) {
        if (obj->tag() >= TAG_EDITOR_EMPTY && obj->tag() != TAG_EDITOR_TOOL_BOX) {
          // select tool box items
          level.setSelectTag(obj->tag());
          tagIndex_ = obj->tagIndex();
          SDL_Log("mouseClicked on [%d]:%d selected.", obj->tag(), tagIndex_);
        }
      }

      int mapTop = SETTINGS.getFixedRowY(0);
      int mapLeft = int(SETTINGS.mapOffsetCol * SETTINGS.cellWidth);
      int mapBottom = int(WORLD_MANAGER.row() * SETTINGS.cellHeight);
      SDL_Log("mouseClicked on [%d, %d] => [%d, %d][%d, %d], Map area(L:%d, B:%d) selected tag: %d.",
              mMouseY, mMouseX, mIndexY, mIndexX, mShiftedY, mShiftedX, mapLeft, mapBottom,
              level.getSelectTag());

      if (level.getSelectTag() >= TAG_EDITOR_EMPTY) {
        if (mMouseY > mapTop && mMouseY <= mapBottom && mMouseX > mapLeft) {
          SDL_Log("Clicked in map area: y=%d => %d; x=%d => %d",
                  mShiftedY, mapBottom, mShiftedX, mapLeft);
          // in map area
          bool mUpdateMap = true;
          switch (level.getSelectTag()) {
            case TAG_EDITOR_EMPTY:
              /* remove block */
              level.getCollisions(mShiftedX, mShiftedY, objectsStore);
              for (std::shared_ptr<GameObject>& obj : objectsStore) {
                if (obj->x() == mShiftedX && obj->y() == mShiftedY) {
                  toRemove = obj;
                }
              }
              mUpdateMap = false;
              break;
            case TAG_EDITOR_PLAYER:
              objectToAdd = std::make_shared<Player>(level, mShiftedX, mShiftedY);
              levelChar = "P";
              break;
            case TAG_EDITOR_GOAL:
              objectToAdd = std::make_shared<Goal>(level, mShiftedX, mShiftedY);
              levelChar = "G";
              break;
            case TAG_EDITOR_COLLECTIBLE:
              collectibleBasePath = SETTINGS.spriteBasePath + "/collectibles/coins/Gold";
              objectToAdd = std::make_shared<Collectible>(level, mShiftedX, mShiftedY, collectibleBasePath, "Gold");
              levelChar = "C";
              break;
            case TAG_EDITOR_POWERUP:
              powerupBasePath = SETTINGS.spriteBasePath + "/collectibles/coins/Silver";
              objectToAdd = std::make_shared<Powerup>(level, mShiftedX, mShiftedY, powerupBasePath, "Silver");
              levelChar = "I";
              break;
            case TAG_EDITOR_BLOCK:
            case TAG_EDITOR_BLOCK_2:
              levelChar = "2";
              objectToAdd = std::make_shared<MapCell>(level, mShiftedX, mShiftedY, 2);
              break;
            case TAG_EDITOR_BLOCK_1:
              levelChar = "1";
              objectToAdd = std::make_shared<MapCell>(level, mShiftedX, mShiftedY, 1);
              break;
            case TAG_EDITOR_BLOCK_3:
              levelChar = "3";
              objectToAdd = std::make_shared<MapCell>(level, mShiftedX, mShiftedY, 3);
              break;
            case TAG_EDITOR_BLOCK_4:
              levelChar = "4";
              objectToAdd = std::make_shared<MapCell>(level, mShiftedX, mShiftedY, 4);
              break;
            case TAG_EDITOR_BLOCK_5:
              levelChar = "5";
              objectToAdd = std::make_shared<MapCell>(level, mShiftedX, mShiftedY, 5);
              break;
            case TAG_EDITOR_BLOCK_6:
              levelChar = "6";
              objectToAdd = std::make_shared<MapCell>(level, mShiftedX, mShiftedY, 6);
              break;
            case TAG_EDITOR_ENEMY:
              levelChar = "E";
              objectToAdd = std::make_shared<Enemy>(level, mShiftedX, mShiftedY);
              break;
            case TAG_EDITOR_BREAK_BLOCK1:
              levelChar = "1";
              objectToAdd = std::make_shared<BreakoutBrick>(level, 1, mShiftedX, mShiftedY);
              break;
            case TAG_EDITOR_BREAK_BLOCK2:
              levelChar = "2";
              objectToAdd = std::make_shared<BreakoutBrick>(level, 2, mShiftedX, mShiftedY);
              break;
            case TAG_EDITOR_BREAK_BLOCK3:
              levelChar = "3";
              objectToAdd = std::make_shared<BreakoutBrick>(level, 3, mShiftedX, mShiftedY);
              break;
            case TAG_EDITOR_BREAK_PADDLE:
              levelChar = "P";
              objectToAdd = std::make_shared<BreakoutPaddle>(level, mShiftedX, mShiftedY);
              break;
            case TAG_EDITOR_BREAK_BALL:
              levelChar = "B";
              objectToAdd = std::make_shared<BreakoutBall>(level, mShiftedX, mShiftedY);
              break;
            case TAG_EDITOR_KEY:
              levelChar = "K";
              objectToAdd = std::make_shared<CustomKey>(level, mShiftedX, mShiftedY,
                                                        SETTINGS.spriteBasePath + "/collectibles/Key", "Key");
              break;
            case TAG_EDITOR_DOOR:
              levelChar = "D";
              objectToAdd = std::make_shared<CustomDoor>(level, mShiftedX, mShiftedY);
              break;
            case TAG_EDITOR_MAGE:
              levelChar = "M";
              objectToAdd = std::make_shared<CustomEnemy>(level, mShiftedX, mShiftedY, 100, 85, 25, "Mage");
              break;
            case TAG_EDITOR_PLAYER_1:
              levelChar = "P";
              objectToAdd = std::make_shared<CustomPlayer>(level, mShiftedX, mShiftedY, 100, 50, 50, "Warrior");
              break;
            default:
              mUpdateMap = false;
              break;
          }

          SDL_Log("edit [%d, %d], org(%s) -> tag[%d] = [%s]",
                  mIndexY, mIndexX, WORLD_MANAGER.getMapChar(mIndexX, mIndexY).c_str(), level.getSelectTag(),
                  levelChar.c_str());
          if (mUpdateMap) {
            mIndexX -= SETTINGS.mapOffsetCol;
            mIndexY -= SETTINGS.mapOffsetRow;
            WORLD_MANAGER.updateMap(mIndexX, mIndexY, levelChar);
          }

          level.setSaved(false);
        } else {
          // if clicked level button
          if (level.getSelectTag() == TAG_EDITOR_LEVEL) {
            WORLD_MANAGER.setLevel(tagIndex_);
            WORLD_MANAGER.loadCurrentLevel();
            level.loadMap();
          }
        }
      }
    }
    if (mouseRightClicked) {
      level.setSelectTag(-1);
    }

    EDIT_TYPE editType = NEW_EDIT;
    if (!mouseLeftClicked && !mouseLeftClicked) {
      editType = processInput(level, objectToAdd, toRemove);
    } else {
      if (level.getSelectTag() == TAG_EDITOR_SAVE) {
        // save map
        SDL_Log("save map to .... [%s]", levelChar.c_str());
        WORLD_MANAGER.saveMap(level, SETTINGS.mapOffsetCol);
      }
    }

    // update level objects
    if (objectToAdd != nullptr) {
      // find object to replace
      level.getCollisions(*objectToAdd, objectsStore);
      for (std::shared_ptr<GameObject>& obj : objectsStore) {
        if (obj->x() == mShiftedX && obj->y() == mShiftedY) {
          toRemove = obj;
        }
      }
    }

    if (editType == NEW_EDIT) {
      EditStep es(objectToAdd, toRemove);
      es.execute(level);
      mUndoStack.push(es);
      mRedoStack = std::stack<EditStep>();
    } else if (editType == UNDO) {
      if (!mUndoStack.empty()) {
        EditStep es = mUndoStack.top();
        es.undo(level);
        mUndoStack.pop();
        mRedoStack.push(es);
      }
    } else if (editType == REDO) {
      if (!mRedoStack.empty()) {
        EditStep es = mRedoStack.top();
        es.redo(level);
        mRedoStack.pop();
        mUndoStack.push(es);
      }
    }
  }
}

EDIT_TYPE EditorInputHandle::processInput(Level& level, std::shared_ptr<GameObject>& objectToAdd, std::shared_ptr<GameObject>& toRemove) {
  EDIT_TYPE et = NEW_EDIT;
  std::string levelChar = ".";

  if (INPUT_MANAGER.isKeyPressed(SDLK_r)) {
    // Remove
    std::vector<std::shared_ptr<GameObject>> objectsStore;
    level.getCollisions(mShiftedX, mShiftedY, objectsStore);
    for (std::shared_ptr<GameObject>& obj : objectsStore) {
      if (obj->x() == mShiftedX && obj->y() == mShiftedY) {
        toRemove = obj;
      }
    }
  } else if (INPUT_MANAGER.isKeyPressed(SDLK_p)) {
    // Character
    levelChar = "P";
    objectToAdd = std::make_shared<Player>(level, mShiftedX, mShiftedY);
  } else if (INPUT_MANAGER.isKeyPressed(SDLK_c)) {
    // Collectible
    levelChar = "C";
    objectToAdd = std::make_shared<Collectible>(level, mShiftedX, mShiftedY, collectibleBasePath, "Gold");
  } else if (INPUT_MANAGER.isKeyPressed(SDLK_e)) {
    // Enemy
    levelChar = "E";
    objectToAdd = std::make_shared<Enemy>(level, mShiftedX, mShiftedY);
  } else if (INPUT_MANAGER.isKeyPressed(SDLK_o)) {
    // Enemy
    levelChar = "R";
    objectToAdd = std::make_shared<Enemy>(level, mShiftedX, mShiftedY);
  } else if (INPUT_MANAGER.isKeyPressed(SDLK_l)) {
    // Enemy
    levelChar = "L";
    objectToAdd = std::make_shared<Goal>(level, mShiftedX, mShiftedY);
  } else if (INPUT_MANAGER.isKeyPressed(SDLK_i)) {
    // Power up
    levelChar = "I";
    objectToAdd = std::make_shared<Powerup>(level, mShiftedX, mShiftedY, powerupBasePath, "Silver");
  } else if (INPUT_MANAGER.isKeyPressed(SDLK_g)) {
    // Goal
    levelChar = "G";
    objectToAdd = std::make_shared<Goal>(level, mShiftedX, mShiftedY);
  } else if (INPUT_MANAGER.isKeyPressed(SDLK_a)) {
    // Map cell
    levelChar = "1";
    objectToAdd = std::make_shared<MapCell>(level, mShiftedX, mShiftedY, 1);
  } else if (INPUT_MANAGER.isKeyPressed(SDLK_s)) {
    // Map cell
    levelChar = "2";
    objectToAdd = std::make_shared<MapCell>(level, mShiftedX, mShiftedY, 2);
  } else if (INPUT_MANAGER.isKeyPressed(SDLK_d)) {
    // Map cell
    levelChar = "3";
    objectToAdd = std::make_shared<MapCell>(level, mShiftedX, mShiftedY, 3);
  } else if (INPUT_MANAGER.isKeyPressed(SDLK_z)) {
    et = UNDO;
  } else if (INPUT_MANAGER.isKeyPressed(SDLK_y)) {
    et = REDO;
  }

  if (et == NEW_EDIT && objectToAdd == nullptr && toRemove == nullptr) {
    et = NONE;
  }

  return et;
}
