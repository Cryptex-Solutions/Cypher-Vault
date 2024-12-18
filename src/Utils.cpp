#include "Utils.h"
#include "OSDetector.h"
#include <cstdlib> // for getenv

std::string Utils::getConfigPath() {
  OSDetector::OS os = OSDetector::getOS();

  switch (os) {
  case OSDetector::OS::Windows:
    return std::string(getenv("APPDATA")) + "\\YourAppName\\config";
  case OSDetector::OS::Linux:
    return std::string(getenv("HOME")) + "/.config/YourAppName";
  case OSDetector::OS::macOS:
    return std::string(getenv("HOME")) +
           "/Library/Application Support/YourAppName";
  default:
    return "./config"; // Fallback to current directory
  }
}

std::string Utils::getDependenciesPath() {
  OSDetector::OS os = OSDetector::getOS();

  switch (os) {
  case OSDetector::OS::Windows:
    return std::string(getenv("APPDATA")) + "\\YourAppName\\dependencies";
  case OSDetector::OS::Linux:
    return std::string(getenv("HOME")) +
           "/.local/share/YourAppName/dependencies";
  case OSDetector::OS::macOS:
    return std::string(getenv("HOME")) +
           "/Library/Application Support/YourAppName/dependencies";
  default:
    return "./dependencies"; // Fallback to current directory
  }
}
