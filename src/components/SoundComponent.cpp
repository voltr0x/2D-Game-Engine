#include "SoundComponent.hpp"
#include "base/GameObject.hpp"
#include "base/Level.hpp"

SoundComponent::SoundComponent(GameObject& gameObject, SFX sfxType)
    : SfxComponent(gameObject) {
  mSfxType = sfxType;
}

void SoundComponent::play(Level& level) {
  GameObject& gameObject = getGameObject();
  switch (mSfxType) {
    case BGM:
      mSoundSource = SETTINGS.backgroundMusic;
      break;
    case JUMP:
      mSoundSource = gameObject.isJump() ? SETTINGS.jumpMusic : "";
      break;
    case REMOVE:
      mSoundSource = level.isCollecting() ? SETTINGS.collectMusic : "";
      break;
    case DIED:
      // if (gameObject.isDead()) {
      //   std::cout << "playSound: " << SETTINGS.diedMusic << std::endl;
      // }
      mSoundSource = gameObject.isDead() ? SETTINGS.diedMusic : "";
      gameObject.die(false);
      break;
  }
  playSound();
}

void SoundComponent::playSound() {
  // if (Mix_Playing(mSfxType) == 0 && !mSoundSource.empty()) {
  if (!mSoundSource.empty()) {
    // Play the music
    // std::cout << "playSound: " << mSoundSource << std::endl;
    if (mSfxType == 0 && Mix_Playing(mSfxType)) {
      return;
    }
    Mix_PlayChannel(mSfxType, RESOURCE_MANAGER.getSoundEffect(mSoundSource), 0);
    if (mSfxType == 0) {
      Mix_Volume(mSfxType, 30);
    } else if (mSfxType == 1) {
      Mix_Volume(mSfxType, 10);
    } else if (mSfxType == 2) {
      Mix_Volume(mSfxType, 50);
    }
  }
}
