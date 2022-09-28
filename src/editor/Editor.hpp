#if !defined(EDITOR_HPP)
#define EDITOR_HPP

#include "../base/SDLGraphicsProgram.hpp"
#include "EditorToolBox.hpp"

const std::string collectibleBasePath = SETTINGS.spriteBasePath + "/collectibles/coins/Gold";
const std::string powerupBasePath = SETTINGS.spriteBasePath + "/collectibles/coins/Silver";

class Editor : public SDLGraphicsProgram {
 public:
  Editor(std::shared_ptr<Level> level);

  void edit();

 private:
  bool editing;
};

#endif  // EDITOR_HPP
