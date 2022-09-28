#if !defined(EDITOR_INPUT_HPP)
#define EDITOR_INPUT_HPP

#include "../Globals.hpp"
#include "../base/GameObject.hpp"
#include "EditorInputHandle.hpp"

class EditorInput : public GameObject {
 private:
  /* data */
 public:
  EditorInput(Level& level)
      : GameObject(level, 0, 0, 0, 0, TAG_IGNORE) {
    addGenericCompenent(std::make_shared<EditorInputHandle>(*this));
  }
};

#endif  // EDITOR_INPUT_HPP
