// code derived from TwinklebearDev SDL 2.0 Tutorial
// https://www.willusher.io/pages/sdl2/

#if !defined(RESOURCE_PATH_HPP)
#define RESOURCE_PATH_HPP

#include <SDL.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <sys/stat.h>

inline char getPathSep() {
#ifdef _WIN32
  const char PATH_SEP = '\\';
#else
  const char PATH_SEP = '/';
#endif
  return PATH_SEP;
}

inline void fixPathSep(std::string& mPath) {
#ifdef _WIN32

  std::string subFolder = mPath;

  if (!subFolder.empty()) {
    std::replace(subFolder.begin(), subFolder.end(), '/', '\\');
  }
#else
  if (!mPath.empty()) {
    std::replace(mPath.begin(), mPath.end(), '\\', '/');
  }
#endif
}

/**
 * @brief Get the resource path for resources located in res/subDir
 *
 * @param subDir
 * @return std::string
 */
inline std::string getResourcePath(const std::string& subDir) {
  // convert delimiter between windows and linux
  std::string subFolder = subDir;

  // We need to choose the path separator properly based on which
  // platform we're running on, since Windows uses a different
  // separator than most systems
#ifdef _WIN32
  const char PATH_SEP = '\\';
  if (!subFolder.empty()) {
    std::replace(subFolder.begin(), subFolder.end(), '/', '\\');
  }
#else
  const char PATH_SEP = '/';
  if (!subFolder.empty()) {
    std::replace(subFolder.begin(), subFolder.end(), '\\', '/');
  }
#endif
  // This will hold the base resource path: Lessons/res/
  // We give it static lifetime so that we'll only need to call
  // SDL_GetBasePath once to get the executable path
  static std::string baseRes;
  if (baseRes.empty()) {
    // SDL_GetBasePath will return NULL if something went wrong in retrieving the path
    char* basePath = SDL_GetBasePath();
    if (basePath) {
      baseRes = basePath;
      SDL_free(basePath);
    } else {
      std::cerr << "Error getting resource path: " << SDL_GetError() << std::endl;
      return "";
    }
    // We replace the last bin/ with res/ to get the the resource path
    size_t pos = baseRes.rfind("bin");
    baseRes = baseRes.substr(0, pos) + "res" + PATH_SEP;
  }
  // If we want a specific subdirectory path in the resource directory
  // append it to the base path. This would be something like Lessons/res/Lesson0
  return subFolder.empty() ? baseRes : baseRes + subFolder + PATH_SEP;
}

/**
 * @brief Get the resource path located in res
 *
 * @param filename
 * @return std::string
 */
inline std::string getResourceName(const std::string& filename) {
  return getResourcePath("") + filename;
}

inline std::string getBinPath(const std::string& subDir) {
  // convert delimiter between windows and linux
  std::string subFolder = subDir;

  // We need to choose the path separator properly based on which
  // platform we're running on, since Windows uses a different
  // separator than most systems
  const char PATH_SEP = getPathSep();
  fixPathSep(subFolder);

  // This will hold the base resource path: Lessons/res/
  // We give it static lifetime so that we'll only need to call
  // SDL_GetBasePath once to get the executable path
  static std::string baseRes;
  if (baseRes.empty()) {
    // SDL_GetBasePath will return NULL if something went wrong in retrieving the path
    char* basePath = SDL_GetBasePath();
    if (basePath) {
      baseRes = basePath;
      SDL_free(basePath);
    } else {
      std::cerr << "Error getting resource path: " << SDL_GetError() << std::endl;
      return "";
    }
    // We replace the last bin/ with res/ to get the the resource path
    size_t pos = baseRes.rfind("bin");
    baseRes = baseRes.substr(0, pos) + "bin" + PATH_SEP;
  }
  // If we want a specific subdirectory path in the resource directory
  // append it to the base path. This would be something like Lessons/res/Lesson0
  return subFolder.empty() ? baseRes : baseRes + subFolder + PATH_SEP;
}

inline std::string getBinName(std::string& filename) {
  std::string mFilename = filename;
  fixPathSep(mFilename);
  return getBinPath("") + filename;
}

inline bool fileExists(const std::string& name) {
  struct stat buffer;   
  return (stat (name.c_str(), &buffer) == 0); 
}

#endif  // RESOURCE_PATH_HPP
