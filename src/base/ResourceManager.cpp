#include "ResourceManager.hpp"
#include <fstream>
#include <sstream>

static const char* TAG = "RESOURCE_MANAGER";

ResourceManager& ResourceManager::getInstance() {
  static ResourceManager* instance = new ResourceManager();
  return *instance;
}

void ResourceManager::startUp(SDL_Renderer* renderer) {
  renderer_ = renderer;

  missingTexture_ = SDL_CreateTexture(renderer_, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1024, 1024);
  SDL_SetRenderTarget(renderer_, missingTexture_);
  SDL_SetRenderDrawColor(renderer_, 0xFF, 0x00, 0xFF, 0xFF);
  SDL_RenderClear(renderer_);
  SDL_SetRenderTarget(renderer_, nullptr);
}

void ResourceManager::shutDown() {
  for (auto& elem : textures_) {
    SDL_DestroyTexture(elem.second);
  }
  SDL_DestroyTexture(missingTexture_);

  for (auto& elem : musics_) {
    Mix_FreeMusic(elem.second);
  }

  for (auto& elem : audioChunks_) {
    Mix_FreeChunk(elem.second);
  }

  fontSizes_.clear();
  textures_.clear();
  musics_.clear();
  audioChunks_.clear();
}

SDL_Texture* ResourceManager::getTexture(const std::string& filename) {
  std::string resource_fileName = getResourceName(filename);
  auto it = textures_.find(resource_fileName);

  if (it != textures_.end()) {
    return it->second;
  } else {
    SDL_Surface* spriteSheet = IMG_Load(resource_fileName.c_str());
    if (spriteSheet == NULL) {
      SDL_Log("Failed to allocate surface from %s", filename.c_str());
      return missingTexture_;
    } else {
      // Create a texture from our surface
      // Textures run faster and take advantage of hardware acceleration
      SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer_, spriteSheet);
      SDL_FreeSurface(spriteSheet);
      textures_.emplace(resource_fileName, texture);
      return texture;
    }
  }
}

bool ResourceManager::unloadTexture(const std::string& filename) {
  std::string resource_fileName = getResourcePath("") + filename;
  auto it = textures_.find(resource_fileName);

  if (it != textures_.end()) {
    SDL_DestroyTexture(it->second);
    textures_.erase(it);
    return true;
  } else {
    return false;
  }
}

Mix_Music* ResourceManager::loadMusic(const std::string& filename) {
  std::string resource_fileName = getResourcePath("") + filename;
  auto it = musics_.find(resource_fileName);

  if (it != musics_.end()) {
    return it->second;
  } else {
    Mix_Music* gMusic = Mix_LoadMUS(resource_fileName.c_str());
    if (gMusic == NULL) {
      SDL_Log("[%s]Failed to load beat music: %s\nSDL_mixer Error: %s\n", TAG, resource_fileName.c_str(), Mix_GetError());
      return nullptr;
    } else {
      musics_.emplace(resource_fileName, gMusic);
      return gMusic;
    }
  }
}

bool ResourceManager::unloadMusic(const std::string& filename) {
  auto it = musics_.find(filename);
  if (it != musics_.end()) {
    Mix_FreeMusic(it->second);
    musics_.erase(it);
    return true;
  } else {
    return false;
  }
}

Mix_Chunk* ResourceManager::getSoundEffect(const std::string& filename) {
  std::string resource_fileName = getResourcePath("") + filename;
  auto it = audioChunks_.find(resource_fileName);

  if (it != audioChunks_.end()) {
    return it->second;
  } else {
    Mix_Chunk* gChunk = Mix_LoadWAV(resource_fileName.c_str());
    if (gChunk == NULL) {
      SDL_Log("[%s]Failed to load beat music! SDL_mixer Error: %s\n", TAG, Mix_GetError());
      SDL_Log("[%s]resource_fileName: %s\n", TAG, resource_fileName.c_str());
      return nullptr;
    } else {
      audioChunks_.emplace(resource_fileName, gChunk);
      return gChunk;
    }
  }
}

bool ResourceManager::unloadSoundEffect(const std::string& filename) {
  auto it = audioChunks_.find(filename);
  if (it != audioChunks_.end()) {
    Mix_FreeChunk(it->second);
    audioChunks_.erase(it);
    return true;
  } else {
    return false;
  }
}

TTF_Font* ResourceManager::getFont(const std::string& filename, int fontSize) {
  std::stringstream fontKey;
  fontKey << "en_" << fontSize << "_" << filename;
  // std::unordered_map<std::string, TTF_Font*>::iterator it;
  auto it = fontSizes_.find(fontKey.str().c_str());

  if (it != fontSizes_.end())
    return it->second;
  else {
    TTF_Font* _font = TTF_OpenFont(getResourceName(filename).c_str(), fontSize);
    if (_font == NULL) {
      SDL_Log("[%s]Failed to load font: %s\nSDL_ttf Error: %s\n", TAG, getResourceName(filename).c_str(), TTF_GetError());
      return nullptr;
    }
    // SDL_Log("Create font [%s], size [%d]", getResourceName(filename).c_str(), fontSize);
    fontSizes_.emplace(fontKey.str().c_str(), _font);
    return _font;
  }
}

TextTexture* ResourceManager::getTextTexture(TTF_Font* font, const std::string& text, const SDL_Color& textColor) {
  auto it = textTextures_.find(text);
  if (it != textTextures_.end()) {
    return it->second;
  } else {
    // As TTF_RenderText_Solid could only be used on
    // SDL_Surface then need to create the surface first
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);

    if (textSurface == NULL) {
      SDL_Log("Failed to allocate surface for given text: %s", text.c_str());
      return nullptr;
    } else {
    TextTexture* mTextTexture = new TextTexture();

    mTextTexture->mRenderer = renderer_;
    mTextTexture->mWidth = textSurface->w;
    mTextTexture->mHeight = textSurface->h;
    // SDL_Log("Create text texture for [%s]", text.c_str());
    // Create a texture from our surface
    // Textures run faster and take advantage of hardware acceleration
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer_, textSurface);
    
    SDL_FreeSurface(textSurface);
    mTextTexture->mTexture = textTexture;
    textTextures_.emplace(text, mTextTexture);
    return mTextTexture;
    }
  }
}