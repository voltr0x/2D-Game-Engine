#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <string>
#include <unordered_map>
#include <vector>
#include "base/ResourcePath.hpp"

//

/**
 * @brief A text texture struct contains
 *
 */
struct TextTexture {
  SDL_Texture* mTexture;
  SDL_Renderer* mRenderer;
  int mWidth;
  int mHeight;

  TextTexture()
      : mTexture(nullptr),
        mWidth(0),
        mHeight(0) {
  }

  SDL_Point size() {
    SDL_Point size;
    SDL_QueryTexture(mTexture, NULL, NULL, &size.x, &size.y);
    return size;
  }

  void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE) {
    SDL_Rect renderRect = {x, y, mWidth, mHeight};
    SDL_RenderCopyEx(mRenderer, mTexture, clip, &renderRect, 0.0f, center, flip);
  }

  void render(SDL_Renderer* gRenderer, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE) {
    SDL_Rect renderRect = {x, y, mWidth, mHeight};
    SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderRect, 0.0f, center, flip);
  }
};

/**
 * @brief A class for managing game resources.
 * Allows access to resources
 * and makes sure there is only one copy of each resource loaded at a
 * time.
 */
class ResourceManager {
 private:
  ResourceManager() = default;                       // Private Singleton
  ResourceManager(ResourceManager const&) = delete;  // Avoid copy constructor.
  void operator=(ResourceManager const&) = delete;   // Don't allow copy assignment.
  ResourceManager(ResourceManager&&) = delete;       // Avoid move constructor.
  void operator=(ResourceManager&&) = delete;        // Don't allow move assignment.

  /**
   * @brief Renderer for the resource manager to use to create textures.
   *
   */
  SDL_Renderer* renderer_ = nullptr;

  /**
   *
   * @brief Hash based map of stored SDL Textures associated to the name of the file the resource was loaded from.
   *
   */
  std::unordered_map<std::string, SDL_Texture*> textures_;

  /**
   *
   * @brief Hash based map of stored music associated to the name of the file the resource was loaded from.
   *
   */
  std::unordered_map<std::string, Mix_Music*> musics_;

  /**
   *
   * @brief Hash based map of stored sound effects associated to the name of the file the resource was loaded from.
   *
   */
  std::unordered_map<std::string, Mix_Chunk*> audioChunks_;

  /**
   *
   * @brief Hash based map of stored text font associated to the name of the file and font size.
   *
   */
  std::unordered_map<std::string, TTF_Font*> fontSizes_;

  /**
   *
   * @brief Hash based map of stored text resources associated to the name of the file the resource was loaded from.
   *
   */
  std::unordered_map<std::string, TextTexture*> textTextures_;

  /**
   * @brief Texture that is rendered if the desired could not be found
   *
   */
  SDL_Texture* missingTexture_ = nullptr;

  /**
   * @brief Vector of level file names
   *
   */
  std::vector<std::string> levelFileNames;

 public:
  /**
   * @brief Gets the instance of the ResourceManager.
   *
   * @return ResourceManager& The manager instance.
   */
  static ResourceManager& getInstance();

  /**
   * @brief Initalize the ResourceManager.
   *
   * @param renderer SDL_Renderer for the ResourceManager to use create textures.
   */
  void startUp(SDL_Renderer* renderer);

  /**
   * @brief Frees any allocated resources.
   *
   */
  void shutDown();

  /**
   * @brief Gets the texture associated with the given file name
   *
   * @param filename If the given file has already been loaded, return the already loaded resource otherwise, load the resource from the file, remember it, and return it. Note: The resource path will be prepended to this path.
   * @return SDL_Texture* A pointer to the resource.
   */
  SDL_Texture* getTexture(const std::string& filename);

  /**
   * @brief Unlaods the texture associated with the given file name
   *
   * @param filename The name of the file whose asset should be unloaded.
   * @return true If the texture was unloaded.
   * @return false If no texture is associated with that filename in the textures_ map.
   */
  bool unloadTexture(const std::string& filename);

  /**
   * @brief Unloads the texture associated with the text if one exists.
   *
   * @param text The key for the texture to be unloaded.
   * @return Whether or not the texture was unlaoded.
   */
  bool unloadTextTexture(const std::string& text);

  /**
   * @brief Get a Mix_Music object for the associated music from a stored map or loads and stores the music from the given filename if it is not already in the mapping.
   *
   * @param filename The name of the file music should be loaded from.
   * @return Mix_Music*  The music object.
   */
  Mix_Music* loadMusic(const std::string& filename);

  /**
   * @brief Unloads the music associated with the given file name if one exists.
   *
   * @param filename The file name the music was loaded from.
   * @return true If the music was found and unloaded.
   * @return false If the music was not unloaded.
   */
  bool unloadMusic(const std::string& filename);

  /**
   * @brief Get a Mix_Chunk object for the associated sound effect from a stored map or loads and stores the sound effect from the given filename if it is not already in the mapping.
   *
   * @param filename The name of the file sound effect should be loaded from.
   * @return Mix_Chunk*  The sound chunk object.
   */
  Mix_Chunk* getSoundEffect(const std::string& filename);

  /**
   * @brief Unloads the sound effect associated with the given file name if one exists.
   *
   * @param filename The file name the sound effect was loaded from.
   * @return true If the sound effect was found and unloaded.
   * @return false If the sound effect was not unloaded.
   */
  bool unloadSoundEffect(const std::string& filename);

  TTF_Font* getFont(const std::string& filename, int fontSize);

  TextTexture* getTextTexture(TTF_Font* font, const std::string& text, const SDL_Color& textColor);
};

#endif
