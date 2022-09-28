#include <cxxtest/TestSuite.h>
#include "base/ResourcePath.hpp"

using namespace std;

class ResourcePathTestSuite : public CxxTest::TestSuite {
 private:
  /* data */

 public:
  
  /**
   * @brief Testing that the get resource functions give the correct string.
   */
  void testGetResourcePath() {
    string baseRes = getResourcePath("");
    size_t pos = baseRes.rfind("res");
    TS_ASSERT_EQUALS(baseRes.substr(pos, sizeof(baseRes)), "res/");

    string pathName = getResourceName("sprites/breakout/ball.bmp");
    pos = baseRes.rfind("res");
    TS_ASSERT_EQUALS(pathName.substr(pos, sizeof(pathName)), "sprites/breakout/ball.bmp");

  }
};
