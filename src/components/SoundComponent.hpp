#if !defined(SOUND_COMPONENT_HPP)
#define SOUND_COMPONENT_HPP

#include "Globals.hpp"
#include "base/SfxComponent.hpp"

class SoundComponent : public SfxComponent {
 public:
  SoundComponent(GameObject& gameObject, SFX sfxType);

  virtual void play(Level& level) override;

  void playSound();

 private:
  SFX mSfxType;
  std::string mSoundSource{""};
};

#endif  // SOUND_COMPONENT_HPP
