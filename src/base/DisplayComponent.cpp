#include "DisplayComponent.hpp"

DisplayComponent::DisplayComponent(GameObject& gameObject)
    : Component(gameObject) {
}

void DisplayComponent::display(Level& level, SDL_Renderer* renderer) {
}