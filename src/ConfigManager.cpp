#include "ConfigManager.h"
#include "Utils.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <toml.h>

// Singleton instance
ConfigManager &ConfigManager::instance() {
  static ConfigManager instance;
  return instance;
}

namespace fs = std::filesystem;

ConfigManager::ConfigManager() {

  configPath = Utils::getConfigPath();
  configFile = configPath + "/settings.toml";

  // Ensure the config directory exists
  if (!fs::exists(configPath)) {
    fs::create_directories(configPath);
    std::cout << "Created config directory: " << configPath << std::endl;
  }

  // Ensure the config file exists
  if (!fs::exists(configFile)) {
    createDefaultConfig();
  }
}

void ConfigManager::createDefaultConfig() {
  toml::table defaultConfig;

  // Add darkmode setting
  defaultConfig.insert("theme_darkmode", false);

  // Save the default configuration to the file
  std::ofstream configFileStream(configFile);
  if (configFileStream) {
    configFileStream << defaultConfig;
    configFileStream.close();
    std::cout << "Created default config file: " << configFile << std::endl;
  } else {
    std::cerr << "Failed to create config file: " << configFile << std::endl;
  }
}

toml::table ConfigManager::loadConfig() {
  try {
    return toml::parse_file(configFile);
  } catch (const toml::parse_error &err) {
    std::cerr << "Error parsing config file: " << err.description() << " at "
              << err.source().begin << std::endl;
    return {};
  }
}