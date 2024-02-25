#include "AudioManager.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_audio.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_timer.h>

#include "Logger.h"
#include "Manager.h"

namespace lb {
AudioManager::AudioManager() {
  setType("AudioManager");
  Log.debug("AudioManager::AudioManager(): Created AudioManager");
}

auto AudioManager::getInstance() -> AudioManager& {
  static AudioManager instance;
  return instance;
}

auto AudioManager::startUp() -> int {
  auto result =
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024);
  if (result != 0) {
    Log.debug("AudioManager::startUp(): failed to open audio %s",
              Mix_GetError());
    return -1;
  }

  return Manager::startUp();
}

auto AudioManager::shutDown() -> void {
  Mix_Quit();
  Manager::shutDown();
}

}  // namespace lb