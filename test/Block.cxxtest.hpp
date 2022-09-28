#include <cxxtest/TestSuite.h>
#include <base/BreakoutLevel.hpp>
#include <breakout/BreakoutObjects.hpp>

// Class to test the block functions
class BlockTestSuite : public CxxTest::TestSuite {
  // data
 private:
 public:
  // Tests the render function
  void testRender() {
    BreakoutLevel* level = new BreakoutLevel();

    level->addObject(std::make_shared<BreakoutBrick>(*level, 1, 100, 100));

    TS_ASSERT_EQUALS(level->getAllObjects().size(), 1);

  }
};
