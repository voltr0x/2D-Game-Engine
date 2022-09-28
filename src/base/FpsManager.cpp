#include "FpsManager.hpp"
#include <iostream>

FpsManager::FpsManager() {
  mStartTicks = SDL_GetTicks();
  countedFrames = 0;
}

int FpsManager::delay() {
  countedFrames++;
  mAvgFps = countedFrames / ((SDL_GetTicks() - mStartTicks) / 1000.0f);
  if (mAvgFps > 2000000) {
    mAvgFps = 0;
  }
  // If frame finished early set limitation / cap fps
  int delay = 0;
  if (mAvgFps >= SCREEN_FPS) {
    delay = SCREEN_TICK_PER_FRAME + mAvgFps - SCREEN_FPS + 1;
    // std::cout << "SCREEN_TICK_PER_FRAME: " << SCREEN_TICK_PER_FRAME
    //           << "; delay: " << delay
    //           << "; FPS: " << mAvgFps
    //           << std::endl;
  }
  return delay;
}
