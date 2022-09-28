#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#include "base/InputManager.hpp"
#include "base/PhysicsManager.hpp"
#include "base/ResourceManager.hpp"
#include "components/WorldManager.hpp"
#include "Settings.hpp"

#define RESOURCE_MANAGER (ResourceManager::getInstance())
#define WORLD_MANAGER (WorldManager::getInstance())
#define PHYSICS_MANAGER (PhysicsManager::getInstance())
#define SETTINGS (Settings::getInstance())

#define INPUT_MANAGER (InputManager::getInstance())

/**
 * @brief type of cell
 *
 */
enum Cell {
  EMPTY,
  BRICK,
  COIN,
  WALL
};

enum SFX {
  BGM,
  JUMP,
  REMOVE,
  DIED
};

static const int CELL_SIZE = SETTINGS.cellSize;
// TODO move to config
static const std::string FONT_NORMAL = "fonts/Junicode.ttf";
static const std::string FONT_MENU = "fonts/PressStart2P-Regular.ttf";
// editor settings
static const int EDITOR_ROW = 4;
static const int EDITOR_COL = 0;

static const int TAG_IGNORE = -1;
static const int TAG_GENERAL = 0;
static const int TAG_PLAYER = 1;
static const int TAG_GOAL = 2;
static const int TAG_BLOCK = 3;
static const int TAG_ENEMY = 4;
static const int TAG_COLLECTIBLE = 5;
static const int TAG_TRIGGER_ZONE = 6;
static const int TAG_POWERUP = 7;
static const int TAG_HEALTH = 8;
static const int TAG_BALL = 9;
static const int TAG_DEAD_ZONE = 10;
static const int TAG_PASSIVE_ENEMY = 11;
static const int TAG_DETECTOR = 12;

static const int TAG_BLOCK_1 = 31;
static const int TAG_BLOCK_2 = 32;
static const int TAG_BLOCK_3 = 33;
static const int TAG_BLOCK_4 = 34;
static const int TAG_BLOCK_5 = 35;
static const int TAG_BLOCK_6 = 36;
static const int TAG_DOOR = 42;
static const int TAG_PLAYER_UI_BOX = 43;
static const int TAG_ENEMEY_UI_BOX = 44;
static const int TAG_PLAYER_1 = 45;

static const int TAG_BORDER_TOP = 50;
static const int TAG_BORDER_RIGHT = 51;
static const int TAG_BORDER_BOTTOM = 52;
static const int TAG_BORDER_LEFT = 53;

static const int TAG_EDITOR_EMPTY = 520;
static const int TAG_EDITOR_PLAYER = 521;
static const int TAG_EDITOR_GOAL = 522;
static const int TAG_EDITOR_BLOCK = 523;
static const int TAG_EDITOR_ENEMY = 524;
static const int TAG_EDITOR_COLLECTIBLE = 525;
static const int TAG_EDITOR_POWERUP = 526;
static const int TAG_EDITOR_TOOL_BOX = 527;
static const int TAG_EDITOR_SAVE = 528;
static const int TAG_EDITOR_LEVEL = 529;

static const int TAG_EDITOR_BLOCK_1 = 531;
static const int TAG_EDITOR_BLOCK_2 = 532;
static const int TAG_EDITOR_BLOCK_3 = 533;
static const int TAG_EDITOR_BLOCK_4 = 534;
static const int TAG_EDITOR_BLOCK_5 = 535;
static const int TAG_EDITOR_BLOCK_6 = 536;

static const int TAG_EDITOR_BREAK_BLOCK1 = 537;
static const int TAG_EDITOR_BREAK_BLOCK2 = 538;
static const int TAG_EDITOR_BREAK_BLOCK3 = 539;
static const int TAG_EDITOR_BREAK_PADDLE = 540;
static const int TAG_EDITOR_BREAK_BALL = 541;

static const int TAG_EDITOR_DOOR = 542;
static const int TAG_EDITOR_KEY = 543;
static const int TAG_EDITOR_HEALTH = 544;
static const int TAG_EDITOR_MAGE = 545;
static const int TAG_EDITOR_PLAYER_1 = 546;
static const int TAG_EDITOR_PASSIVE_ENEMY = 547;
static const int TAG_EDITOR_DETECTOR = 548;

static const int TAG_BUTTON = 100;
static const int TAG_TB_LAUNCH = 101;
static const int TAG_BUTTON_BREAKOUT = 110;
static const int TAG_BUTTON_BREAKOUT_EDITOR = 111;
static const int TAG_TB_BREAKOUT_EDITOR = 112;
static const int TAG_BUTTON_PLATFORMER = 120;
static const int TAG_BUTTON_PLATFORMER_EDITOR = 121;
static const int TAG_TB_PLATFORMER_EDITOR = 122;
static const int TAG_BUTTON_CUSTOM = 130;
static const int TAG_BUTTON_CUSTOM_EDITOR = 131;
static const int TAG_TB_CUSTOM_EDITOR = 132;
static const int TAG_COIN = 140;

// static std::unordered_map<std::string, int> CHAR_TAG_MAP;
// static std::unordered_map<int, std::string> TAG_CHAR_MAP;

static const int STATE_QUIT = -1;
//!< game state: 0; start, 1: running, 2: win, 3, fallen, 4, killed 5, timeout
static const int STATE_START = 0;
static const int STATE_RUNING = 1;
static const int STATE_WIN = 2;
static const int STATE_LOSE = 3;  //!< game is over
// static const int STATE_FALLEN= 3;
static const int STATE_KILLED = 4;  //!< just loss live not lose game yet
static const int STATE_EDITOR = 5;
static const int STATE_EDITOR_LEVEL = 6;
static const int STATE_PAUSE = 7;
static const int STATE_EDITOR_LAUNCH = 10;

static const int POS_TOP = 0;
static const int POS_RIGHT = 1;
static const int POS_BOTTOM = 2;
static const int POS_LEFT = 3;

static const int BORDER_SIZE = 10;

#endif