#ifndef EDITORLEVEL_LEVEL_HPP
#define EDITORLEVEL_LEVEL_HPP

#include "../base/Level.hpp"

class EditorLevel : public Level {
 public:
  EditorLevel();

  void initialize() override;

  void loadMap() override;

  void addObjectToLevel(float x, float y, char objectType);

  inline void revive() override{};

 private:
  std::shared_ptr<Level> mEditorLevel;
};
#endif  // EDITORLEVEL_LEVEL_HPP