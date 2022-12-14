#if !defined(BASE_INPUT_MANAGER)
#define BASE_INPUT_MANAGER

#include <SDL.h>
#include <set>

//! \brief Class for managing (keyboard) input.
class InputManager {
 private:
  InputManager() = default;                      // Private Singleton
  InputManager(InputManager const&) = delete;    // Avoid copy constructor.
  void operator=(InputManager const&) = delete;  // Don't allow copy assignment.

 public:
  static InputManager& getInstance();  //!< Get the instance.

  void startUp();
  void shutDown();

  void resetForFrame();                    //!< Reset key state for a new frame.
  void handleEvent(const SDL_Event& e);    //!< Update key state based on an event.
  bool isKeyDown(SDL_Keycode k) const;     //!< Get if a key is currently down.
  bool isKeyPressed(SDL_Keycode k) const;  //!< Get if a key was pressed this frame.

  bool isMouseDown(Uint8 k) const;     //!< Get if a key is currently down.
  bool isMousePressed(Uint8 k) const;  //!< Get if a key was pressed this frame.

 private:
  std::set<SDL_Keycode> mKeysDown;
  std::set<SDL_Keycode> mKeysPressed;

  std::set<Uint8> mMouseDown;
  std::set<Uint8> mMousePressed;
};

#endif  // BASE_INPUT_MANAGER
