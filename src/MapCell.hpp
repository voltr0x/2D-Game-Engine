#if !defined(MAP_CELL_HPP)
#define MAP_CELL_HPP

#include <string>
#include <sstream>
#include "Globals.hpp"
#include "base/GameObject.hpp"
#include "base/PhysicsComponent.hpp"
#include "base/RenderBlockComponent.hpp"

/**
 * @brief The block object for creating blocks.
 *
 */
class MapCell : public GameObject {
 public:
  MapCell(Level& level, float x, float y, int tileId)
      : GameObject(level, x, y, SETTINGS.cellWidth, SETTINGS.cellHeight, TAG_BLOCK) {
    setPhysicsCompenent(std::make_shared<PhysicsComponent>(*this, PhysicsComponent::Type::STATIC_SOLID));

    std::stringstream blockSpriteName;
    blockSpriteName << SETTINGS.spriteBasePath << "/tiles/" << tileId << ".png";
    setRenderCompenent(std::make_shared<RenderBlockComponent>(*this, blockSpriteName.str()));
  }
};

#endif  // MAP_CELL_HPP
