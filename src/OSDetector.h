#ifndef OS_DETECTOR_H
#define OS_DETECTOR_H

class OSDetector {
public:
  enum class OS { Windows, macOS, Linux, Unix, POSIX, Unknown };

  static OS getOS() {
#if defined(_WIN32) || defined(_WIN64)
    return OS::Windows;
#elif defined(__APPLE__) || defined(__MACH__)
    return OS::macOS;
#elif defined(__linux__)
    return OS::Linux;
#elif defined(__unix__)
    return OS::Unix;
#elif defined(_POSIX_VERSION)
    return OS::POSIX;
#else
    return OS::Unknown;
#endif
  }
};

#endif // OS_DETECTOR_H
