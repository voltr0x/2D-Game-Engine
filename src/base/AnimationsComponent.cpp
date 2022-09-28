#include "base/AnimationsComponent.hpp"
#include "base/GameObject.hpp"
#include "base/Level.hpp"
#include <cmath>

AnimationsComponent::AnimationsComponent(GameObject& gameObject) : Component(gameObject) {}


StaticAnimationsComponent::StaticAnimationsComponent(GameObject & gameObject, std::string basePath, std::string prefix, int max)
 : AnimationsComponent(gameObject), basePath_(basePath), prefix_(prefix), max_(max) {}

void StaticAnimationsComponent::animate() {
    count++;
}

std::string StaticAnimationsComponent::getCurrent() {
    return basePath_ + "/" + prefix_ + "_" + std::to_string(count / 5 % max_+1) + ".png";
}

DynamicAnimationsComponent::DynamicAnimationsComponent(GameObject & gameObject, std::string basePath, std::vector<std::pair<std::string,int>> prefixes) 
 : AnimationsComponent(gameObject), basePath_(basePath), prefixes_(prefixes) {}

void DynamicAnimationsComponent::animate() {
    count++;
}

std::string DynamicAnimationsComponent::getCurrent() {
    GameObject& gameObject = getGameObject();
    std::pair<std::string,int> prefix;
    // idle, walk , jump
    if (gameObject.isJump())
        prefix = prefixes_[2];
    if (gameObject.isOnGround() && !gameObject.isLeft() && !gameObject.isRight()) {
        prefix = prefixes_[0];
    } else {
        prefix = prefixes_[1];
    }
    // jump
    // walk
    return basePath_ + "/" + prefix.first + "/" + prefix.first + std::to_string(count / 10 % prefix.second+1) + ".png";
}