#ifndef SINGLETON_HPP
#define SINGLETON_HPP

template <class T>
class Singleton {
 private:
  /* data */
  static T* instance;
  ~Singleton() {}

 public:
  Singleton() = default;                      // Private Singleton
  Singleton(Singleton const&) = delete;       // Avoid copy constructor.
  void operator=(Singleton const&) = delete;  // Don't allow copy assignment.
  Singleton(Singleton&&) = delete;            // Avoid move constructor.
  void operator=(Singleton&&) = delete;       // Don't allow move assignment.

  /**
   * Create a new Singleton instance.
   */
  static void createInstance() {
    instance = new T();
  }

  /**
   * Destroy the Singleton instance.
   */
  static void destroyInstance() {
    delete instance;
    instance = 0;
  }

  /**
   * @brief Gets the instance of the singleton.
   *
   * @return T& The singleton instance.
   */
  static T& getInstance() {
    return *instance;
  }

  /**
   * @brief Set the instance used by the Singleton.
   *
   * @param newInstance the new instance to use.
   */
  static void setInstance(T* newInstance) {
    if (instance)
      destroyInstance();
    instance = newInstance;
  }
};

template <class T>
T* Singleton<T>::instance = 0;

#endif