#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <iostream>

static const std::string PLATFORMER_SETTINGS_FILE_NAME = "configs/platformer_settings.ini";
static const std::string BREAKOUT_SETTINGS_FILE_NAME = "configs/breakout_settings.ini";
static const std::string CUSTOM_SETTINGS_FILE_NAME = "configs/custom_settings.ini";

/**
 * @brief Game settings loaded from the res/configs/xxx_settings.ini.
 *
 */
class Settings {
 private:
  Settings() = default;                      // Private Singleton
  Settings(Settings const&) = delete;        // Avoid copy constructor.
  void operator=(Settings const&) = delete;  // Don't allow copy assignment.
  Settings(Settings&&) = delete;             // Avoid move constructor.
  void operator=(Settings&&) = delete;       // Don't allow move assignment.

 public:
  int screenWidth{1024};  ///< screen width in pixels.
  int screenHeight{768};  ///< screen height in pixels.

  bool showTopBar{false};
  int topBarHeight{40};  ///< not from ini file

  int cellSize{64};

  int cellWidth{64};
  int cellHeight{64};
  int editorRows{4};
  int editorCols{3};

  int mapOffsetCol{0};
  int mapOffsetRow{0};

  bool fullscreen{false};  ///< Full screen on/off.
  bool debugMode{false};   ///< Debug mode on/off.
  std::string appName{"Nil..."};

  std::string backgroundMusic{""};
  std::string jumpMusic{""};
  std::string collectMusic{""};
  std::string diedMusic{""};
  std::string winMusic{""};
  std::string loseMusic{""};
  std::string levelListLocation{""};
  std::string gameType{""};
  int lives{1};

  // [font]
  std::string fontName{""};
  int fontSize{22};

  // [assets]
  std::string spriteBasePath{""};

  /**
   * Initializes with default settings.
   */
  inline static Settings& getInstance() {
    static Settings* instance = new Settings();
    return *instance;
  };

  inline int getFixedColX(const int col) {
    return (col + mapOffsetCol) * cellWidth;
  };

  inline float getFixedX(const float x) {
    return x + (mapOffsetCol * cellWidth);
  };

  inline int getFixedRowY(const int row) {
    int mY = (row + mapOffsetRow) * cellHeight;
    if (showTopBar) {
      mY += topBarHeight;
    }
    return mY;
  };

  inline float getFixedY(const float y) {
    float mY = y + (mapOffsetRow * cellHeight);
    if (showTopBar) {
      mY += topBarHeight;
    }
    return mY;
  };
};

#endif  // SETTINGS_HPP
