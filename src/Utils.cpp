#include "Utils.h"
#include "OSDetector.h"
#include <cstdlib> // for getenv

std::string Utils::getConfigPath() {
  switch (OSDetector::getOS()) { // Use the static detected OS directly
  case OSDetector::OS::Windows:
    return std::string(getenv("APPDATA")) + "\\CypherVault\\config";
  case OSDetector::OS::Linux:
    return std::string(getenv("HOME")) + "/.config/CypherVault";
  case OSDetector::OS::macOS:
    return std::string(getenv("HOME")) +
           "/Library/Application Support/CypherVault";
  default:
    return "./config"; // Fallback to current directory
  }
}

std::string Utils::getDependenciesPath() {
  switch (OSDetector::getOS()) { // Use the static detected OS directly
  case OSDetector::OS::Windows:
    return std::string(getenv("APPDATA")) + "\\CypherVault\\dependencies";
  case OSDetector::OS::Linux:
    return std::string(getenv("HOME")) +
           "/.local/share/CypherVault/dependencies";
  case OSDetector::OS::macOS:
    return std::string(getenv("HOME")) +
           "/Library/Application Support/CypherVault/dependencies";
  default:
    return "./dependencies"; // Fallback to current directory
  }
}
