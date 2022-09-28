#include "base/PhysicsComponent.hpp"
#include "base/GameObject.hpp"
#include "base/Level.hpp"
#include "base/PhysicsManager.hpp"

PhysicsComponent::PhysicsComponent(GameObject& gameObject, Type type)
    : Component(gameObject),
      mType(type) {
  mDensity = type == Type::DYNAMIC_SOLID ? 1.0f : 0.0f;
  initBox2d(gameObject);
}

PhysicsComponent::PhysicsComponent(GameObject& gameObject, Type type, float density, float friction, float restitution)
    : Component(gameObject),
      mType(type),
      mDensity(density),
      mFriction(friction),
      mRestitution(restitution) {
  initBox2d(gameObject);
}

PhysicsComponent::PhysicsComponent(GameObject& gameObject, bool type)
    : Component(gameObject) {
  mType = type ? Type::STATIC_SOLID : Type::DYNAMIC_SOLID;
  initBox2d(gameObject);
}

PhysicsComponent::~PhysicsComponent() {
  PhysicsManager::getInstance().getWorld()->DestroyBody(mBody);
  mBody = nullptr;
}

void PhysicsComponent::initBox2d(GameObject& gameObject) {
  b2BodyDef bodyDef;
  b2FixtureDef fixtureDef;

  bodyDef.type = (mType == Type::DYNAMIC_SOLID ? b2_dynamicBody : b2_staticBody);

  bodyDef.position.x = (gameObject.x() + 0.5f * gameObject.w()) * PhysicsManager::GAME_TO_PHYSICS_SCALE;
  bodyDef.position.y = (gameObject.y() + 0.5f * gameObject.h()) * PhysicsManager::GAME_TO_PHYSICS_SCALE;
  bodyDef.linearDamping = 2.0f;
  bodyDef.fixedRotation = true;
  //!< to associate the gameCbject with the phsicis body
  bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(&gameObject);
  mBody = PhysicsManager::getInstance().getWorld()->CreateBody(&bodyDef);

  // add a fixture to the body
  b2PolygonShape polygonShape;
  polygonShape.SetAsBox(0.495 * gameObject.w() * PhysicsManager::GAME_TO_PHYSICS_SCALE, 0.495 * gameObject.h() * PhysicsManager::GAME_TO_PHYSICS_SCALE);  // a 4x2 rectangle

  fixtureDef.shape = &polygonShape;
  fixtureDef.density = mDensity;
  fixtureDef.friction = mFriction;
  fixtureDef.restitution = mRestitution;
  fixtureDef.isSensor = (mType == Type::STATIC_SENSOR);

  mBody->CreateFixture(&fixtureDef);
}

void PhysicsComponent::setVx(float vx) {
  mBody->SetLinearVelocity(b2Vec2(vx * PhysicsManager::GAME_TO_PHYSICS_SCALE, mBody->GetLinearVelocity().y));
}

void PhysicsComponent::setVy(float vy) {
  mBody->SetLinearVelocity(b2Vec2(mBody->GetLinearVelocity().x, vy * PhysicsManager::GAME_TO_PHYSICS_SCALE));
}

void PhysicsComponent::addFx(float fx) {
  mBody->ApplyForce(b2Vec2(fx * PhysicsManager::GAME_TO_PHYSICS_SCALE, 0.0f), mBody->GetPosition(), true);
}

void PhysicsComponent::addFy(float fy) {
  mBody->ApplyForce(b2Vec2(0.0f, fy * PhysicsManager::GAME_TO_PHYSICS_SCALE), mBody->GetPosition(), true);
}

void PhysicsComponent::addLinearForce(float fx, float fy) {
  mBody->ApplyLinearImpulse(b2Vec2(fx, fy), mBody->GetPosition(), true);
}

void PhysicsComponent::postStep() {
  b2Vec2 position = mBody->GetPosition();

  GameObject& gameObject = getGameObject();
  gameObject.setX(position.x / PhysicsManager::GAME_TO_PHYSICS_SCALE - 0.5f * gameObject.w());
  gameObject.setY(position.y / PhysicsManager::GAME_TO_PHYSICS_SCALE - 0.5f * gameObject.h());
}