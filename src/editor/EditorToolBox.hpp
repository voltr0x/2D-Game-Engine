#if !defined(EDITOR_TOOL_BOX_HPP)
#define EDITOR_TOOL_BOX_HPP

#include "../Globals.hpp"
#include "../base/GameObject.hpp"
#include "EditorToolBoxRender.hpp"

class EditorToolBox : public GameObject {
 public:
  EditorToolBox(Level& level, int tag)
      : GameObject(level, 0, 0, SETTINGS.screenWidth, int(SETTINGS.editorRows * SETTINGS.cellHeight), tag) {
    int _y = int(WORLD_MANAGER.row() * SETTINGS.cellHeight);
    this->setY(SETTINGS.getFixedY(_y));

    setDisplayCompenent(std::make_shared<EditorToolBoxRender>(*this));
  }
};

#endif  // EDITOR_TOOL_BOX_HPP
