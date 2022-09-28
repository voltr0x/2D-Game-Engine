#include <cxxtest/TestSuite.h>
#include "base/ResourceManager.hpp"
#include "iostream"

class ResourceManagerTestSuite: public CxxTest::TestSuite
{
public:
    /**
   * @brief Testing that the correct texture is gotten from the resource manager.
   */
    void testGetTexture(){
        SDL_Window* window = SDL_CreateWindow("Breakout test!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0, SDL_WINDOW_HIDDEN);

        SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        ResourceManager::getInstance().startUp(renderer);
        SDL_Texture* texture = ResourceManager::getInstance().getTexture("paddle.bmp");

        TS_ASSERT(texture != nullptr);
    }

};