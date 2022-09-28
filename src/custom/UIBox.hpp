#if !defined(UI_BOX_HPP)
#define UI_BOX_HPP

#include "../Globals.hpp"
#include "../base/GameObject.hpp"
#include "UIBoxRender.hpp"

/**
 * Sets up display for the UIbox.
 */
class UIBox : public GameObject {
 public:
  UIBox(Level& level, int tag)
      : GameObject(level, 0, 0, 0, 0, tag) {
    if (SETTINGS.showTopBar) {
      this->setY(this->y() + SETTINGS.topBarHeight);
    }
    setDisplayCompenent(std::make_shared<UIBoxRender>(*this));
  }
};

#endif  // EDITOR_TOOL_BOX_HPP
