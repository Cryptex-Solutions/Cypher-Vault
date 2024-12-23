#include "Utils.h"
#include "OSDetector.h"
#include <cstdlib>

std::string Utils::getConfigPath() {
  switch (OSDetector::getOS()) {
  case OSDetector::OS::Windows:
    return std::string(getenv("APPDATA")) + "\\CypherVault\\config";
  case OSDetector::OS::Linux:
    return std::string(getenv("HOME")) + "/.config/CypherVault";
  case OSDetector::OS::macOS:
    return std::string(getenv("HOME")) +
           "/Library/Application Support/CypherVault";
  default:
    return "./config";
  }
}

std::string Utils::getDependenciesPath() {
  switch (OSDetector::getOS()) {
  case OSDetector::OS::Windows:
    return std::string(getenv("APPDATA")) + "\\CypherVault\\dependencies";
  case OSDetector::OS::Linux:
    return std::string(getenv("HOME")) +
           "/.local/share/CypherVault/dependencies";
  case OSDetector::OS::macOS:
    return std::string(getenv("HOME")) +
           "/Library/Application Support/CypherVault/dependencies";
  default:
    return "./dependencies";
  }
}
