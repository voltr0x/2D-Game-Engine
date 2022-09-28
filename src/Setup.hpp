#if !defined(SETUP_HPP)
#define SETUP_HPP

#include <iostream>
#include "Globals.hpp"
#include "lib/SimpleIni.h"

// String conversion function
template <typename T>
static T convertString(const std::string& str){};

template <>
std::string convertString(const std::string& str) {
  return str;
}

template <>
int convertString(const std::string& str) {
  return atoi(str.c_str());
}

template <>
bool convertString(const std::string& str) {
  return (convertString<int>(str) != 0);
}

template <typename T>
static void loadSettingValue(const CSimpleIniA& iniFile, const std::string& section, const std::string& key, T& setting) {
  const char* value = nullptr;
  value = iniFile.GetValue(section.c_str(), key.c_str());

  if (value != nullptr) {
    setting = convertString<T>(value);
    std::cout << "Setting[" << key << "] = " << setting << std::endl;
  } else {
    std::cout << "Setting[" << key << "] not set. Default: " << setting << std::endl;
  }
}

/**
 * @brief load settings before game running
 * 
 */
static void loadSettings(const std::string& settingsFileName) {
  std::cout << "Loading settings from: " << settingsFileName << std::endl;
  CSimpleIniA iniFile;
  iniFile.SetUnicode();

  SI_Error rc = iniFile.LoadFile(getResourceName(settingsFileName).c_str());
  if (rc < 0) { /* handle error */
    std::cout << "[Settings]unable to open setting file: " << settingsFileName << std::endl;
  }

#define LOAD_SETTING(type, section, key) loadSettingValue<type>(iniFile, section, #key, SETTINGS.key)
  // [window]
  LOAD_SETTING(int, "window", screenWidth);
  LOAD_SETTING(int, "window", screenHeight);
  LOAD_SETTING(bool, "window", fullscreen);
  LOAD_SETTING(int, "window", editorRows);
  LOAD_SETTING(std::string, "window", appName);

  LOAD_SETTING(bool, "window", showTopBar);

  // [game]
  LOAD_SETTING(bool, "game", debugMode);
  LOAD_SETTING(int, "game", cellSize);
  LOAD_SETTING(int, "game", cellWidth);
  LOAD_SETTING(int, "game", cellHeight);
  LOAD_SETTING(std::string, "game", levelListLocation);
  LOAD_SETTING(std::string, "game", gameType);
  LOAD_SETTING(int, "game", lives);

  // [audio]
  LOAD_SETTING(std::string, "audio", backgroundMusic);
  LOAD_SETTING(std::string, "audio", jumpMusic);
  LOAD_SETTING(std::string, "audio", collectMusic);
  LOAD_SETTING(std::string, "audio", diedMusic);

  // [font]
  LOAD_SETTING(std::string, "font", fontName);
  LOAD_SETTING(int, "font", fontSize);
  // [Editor]
  LOAD_SETTING(int, "editor", mapOffsetCol);
  LOAD_SETTING(int, "editor", mapOffsetRow);

  // load font
  // RESOURCE_MANAGER.loadFont(SETTINGS.fontName);

  // [assets]
  LOAD_SETTING(std::string, "assets", spriteBasePath);
}

#endif  // SETUP_HPP
