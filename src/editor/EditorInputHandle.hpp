#if !defined(EDITOR_INPUT_HANDLE_HPP)
#define EDITOR_INPUT_HANDLE_HPP

#include "../base/GenericComponent.hpp"
#include "../base/Level.hpp"
#include <stack>


enum EDIT_TYPE {
  NEW_EDIT,
  UNDO,
  REDO,
  NONE
};

class EditStep {
private:
  std::shared_ptr<GameObject> objectToAdd = nullptr;
  std::shared_ptr<GameObject> toRemove = nullptr;
public:

  EditStep(std::shared_ptr<GameObject>& add, std::shared_ptr<GameObject>& remove){
    objectToAdd = add;
    toRemove = remove;
  }

  void execute(Level& level){
    if(objectToAdd){
      level.addObject(objectToAdd);
    }
    if(toRemove){
      level.removeObject(toRemove);
    }
  }

  void undo(Level& level){
    if(objectToAdd){
      level.removeObject(objectToAdd);
    }
    if(toRemove){
      level.addObject(toRemove);
    }
  }

  void redo(Level& level){
    execute(level);
  }

};


class EditorInputHandle : public GenericComponent {
 private:
  /* data */
  int mMouseX{0}, mMouseY{0};
  int mShiftedX{0}, mShiftedY{0};
  int mIndexX{0}, mIndexY{0};
  std::stack<EditStep> mUndoStack;
  std::stack<EditStep> mRedoStack;

  EDIT_TYPE processInput(Level& level, std::shared_ptr<GameObject>& objectToAdd, std::shared_ptr<GameObject>& toRemove);

 public:
  EditorInputHandle(GameObject& gameObject);

  virtual void update(Level& level) override;
};

#endif  // EDITOR_INPUT_HANDLE_HPP
