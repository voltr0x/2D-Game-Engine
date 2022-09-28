#include "base/PatrolComponent.hpp"
#include "Level.hpp"
#include "base/GameObject.hpp"
#include "iostream"

PatrolComponent::PatrolComponent(GameObject& gameObject, std::vector<std::pair<float, float>> locs, float speed)
    : GenericComponent(gameObject), speed_(speed), count(0) {
  // TODO: initialization
  for (auto p : locs) {
    m_locs.push_back(p);
  }
  m_locs.emplace_back(std::make_pair(gameObject.x(), gameObject.y()));
  index = m_locs.size();
}

void PatrolComponent::update(Level& level) {
  if (level.isGameOver()) {
    return;
  }
  
  GameObject& gameObject = getGameObject();
  std::shared_ptr<PhysicsComponent> pc = gameObject.physicsComponent();
  std::pair curr = m_locs[count % index];
  if (gameObject.x() < curr.first) {
    gameObject.setRight(true);
    gameObject.setLeft(false);
    pc->setVx(speed_);
  } else if (gameObject.x() > curr.first) {
    gameObject.setLeft(true);
    gameObject.setRight(false);
    pc->setVx(-speed_);
  } else {
    pc->setVx(0.0f);
  }
  if (gameObject.y() < curr.second) {
    pc->setVy(speed_);
  } else if (gameObject.y() > curr.second) {
    pc->setVy(-speed_);
  } else {
    pc->setVy(0.0f);
  }
  if (gameObject.x() == curr.first && gameObject.y() == curr.second) {
    count++;
  }
  
}
