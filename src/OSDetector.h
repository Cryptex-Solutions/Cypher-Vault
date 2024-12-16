#ifndef OSDETECTOR_H
#define OSDETECTOR_H

#include <string>

class OSDetector {
public:
  enum OSType { Windows, Linux, MacOS, Unknown };

  // Function to get the OS type
  static OSType getOSType() {
#ifdef _WIN32
    return Windows;
#elif __linux__
    return Linux;
#elif __APPLE__
    return MacOS;
#else
    return Unknown;
#endif
  }

  // Function to get the OS name as a string
  static std::string getOSName() {
    switch (getOSType()) {
    case Windows:
      return "Windows";
    case Linux:
      return "Linux";
    case MacOS:
      return "MacOS";
    default:
      return "Unknown";
    }
  }
};

#endif // OSDETECTOR_H
