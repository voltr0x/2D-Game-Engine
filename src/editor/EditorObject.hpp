#if !defined(EDITOR_OBJECT_HPP)
#define EDITOR_OBJECT_HPP

#include "../Globals.hpp"
#include "../base/GameObject.hpp"
#include "EditorToolBoxRender.hpp"

class EditorObject : public GameObject {
 private:
  /* data */
 public:
  inline EditorObject(Level& level, int posX, int posY, int tag)
      : GameObject(level, posX * SETTINGS.cellWidth, posY * SETTINGS.cellHeight, SETTINGS.cellWidth, SETTINGS.cellHeight, tag) {
    this->setY(SETTINGS.getFixedY(this->y()));
    setDisplayCompenent(std::make_shared<EditorToolBoxRender>(*this));
  }
};

class EditorLevelButton : public GameObject {
 private:
  /* data */
 public:
  inline EditorLevelButton(Level& level, int posX, int posY, int tag, int tagIndex)
      : GameObject(level, posX * SETTINGS.cellWidth, posY * SETTINGS.cellHeight, SETTINGS.cellWidth, SETTINGS.cellHeight, tag) {
    if (tag == TAG_EDITOR_LEVEL) {
      this->setTagIndex(tagIndex);
    }
    this->setY(SETTINGS.getFixedY(this->y()));
    setDisplayCompenent(std::make_shared<EditorToolBoxRender>(*this));
  }
};

#endif  // EDITOR_OBJECT_HPP
