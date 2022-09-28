// Support Code written by Michael D. Shah
// Updated by Seth Cooper
// Please do not redistribute without asking permission.

#include "SDLGraphicsProgram.hpp"
#include <time.h>
#include <iostream>
#include <sstream>
#include "FpsManager.hpp"
#include "InputManager.hpp"
#include "PhysicsManager.hpp"
#include "ResourceManager.hpp"

// Initialization function
SDLGraphicsProgram::SDLGraphicsProgram(std::shared_ptr<Level> level)
    : mLevel(level) {
  // Initialize random number generation.
  srand(time(nullptr));

  // Initialization flag
  bool success = true;
  // String to hold any errors that occur.
  std::stringstream errorStream;
  // The window we'll be rendering to
  mWindow = nullptr;

  // Initialize SDL
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    errorStream << "SDL could not initialize! SDL Error: " << SDL_GetError() << "\n";
    success = false;
  } else {
    // Create window
    mWindow = SDL_CreateWindow(mLevel->title().c_str(), 100, 100, mLevel->w(), mLevel->h(), SDL_WINDOW_SHOWN);

    // Check if Window did not create.
    if (mWindow == nullptr) {
      errorStream << "Window could not be created! SDL Error: " << SDL_GetError() << "\n";
      success = false;
    }

    // Create a Renderer to draw on
    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
    // Check if Renderer did not create.
    if (mRenderer == nullptr) {
      errorStream << "Renderer could not be created! SDL Error: " << SDL_GetError() << "\n";
      success = false;
    }

    // Initialize SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
      printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
      success = false;
    }

    // Initialize SDL_ttf
    if (TTF_Init() == -1) {
      printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
      success = false;
    }
  }

  InputManager::getInstance().startUp();
  PhysicsManager::getInstance().startUp();
  ResourceManager::getInstance().startUp(mRenderer);

  // If initialization did not work, then print out a list of errors in the constructor.
  if (!success) {
    errorStream << "Failed to initialize!\n";
    std::string errors = errorStream.str();
    std::cout << errors << "\n";
  } else {
    std::cout << "No SDL errors Detected in during init\n\n";
  }
}

// Proper shutdown and destroy initialized objects
SDLGraphicsProgram::~SDLGraphicsProgram() {
  InputManager::getInstance().shutDown();

  // Destroy Renderer
  SDL_DestroyRenderer(mRenderer);
  mRenderer = nullptr;

  // Destroy window
  SDL_DestroyWindow(mWindow);
  mWindow = nullptr;

  // Quit SDL subsystems
  SDL_Quit();
}

// Update OpenGL
void SDLGraphicsProgram::update() {
  mLevel->update();
}

// Render
// The render function gets called once per loop
void SDLGraphicsProgram::render() {
  // TODO move background color to config
  SDL_SetRenderDrawColor(mRenderer, 0x32, 0x22, 0x22, 0xFF);
  SDL_RenderClear(mRenderer);

  mLevel->render(mRenderer);
  mLevel->display(mRenderer);

  SDL_RenderPresent(mRenderer);
}

// play sound
void SDLGraphicsProgram::play() {
  mLevel->play();
}
// Loops forever!
void SDLGraphicsProgram::loop() {
  // Main loop flag
  // If this is quit = 'true' then the program terminates.
  // using mLevel->state() to control termination
  // bool quit = false;
  // Event handler that handles various events in SDL
  // that are related to input and output
  SDL_Event e;

  // initialize current level
  mLevel->initialize();

  // Fps cap
  FpsManager fpsManager;

  // While application is running
  while (mLevel->state() >= 0) {
    InputManager::getInstance().resetForFrame();

    // Handle events on queue
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        // quit = true;
        mLevel->setState(-1);
      }
      if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_n) {
        mLevel->nextLevel();
      }
      if(e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_o) {
        mLevel->toggleRandomLevelMode();
      }
      InputManager::getInstance().handleEvent(e);
    }

    // update
    update();

    // render
    render();

    // play sound
    play();

    // update fps Reduce framerate
    SDL_Delay(fpsManager.delay());
    mLevel->setFps(fpsManager.avgFps());
  }
  mLevel->finalize();
}
