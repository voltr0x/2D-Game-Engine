#if !defined(BASE_FPS_MANAGER_HPP)
#define BASE_FPS_MANAGER_HPP

#include <SDL.h>

const int SCREEN_FPS = 60;
const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;

class FpsManager {
 private:
  /* data */
  // The clock time when the timer started
  Uint32 mStartTicks;
  float mAvgFps;
  int countedFrames;

 public:
  FpsManager(/* args */);
  int delay();

  inline float avgFps() { return mAvgFps; }
};

#endif  // BASE_FPS_MANAGER_HPP
