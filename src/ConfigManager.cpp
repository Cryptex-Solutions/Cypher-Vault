#include "ConfigManager.h"
#include "Utils.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <toml.h>

ConfigManager &ConfigManager::instance() {
  static ConfigManager instance;
  return instance;
}

namespace fs = std::filesystem;

ConfigManager::ConfigManager() {

  configPath = Utils::getConfigPath();
  configFile = configPath + "/settings.toml";

  if (!fs::exists(configPath)) {
    fs::create_directories(configPath);
    std::cout << "Created config directory: " << configPath << std::endl;
  }

  if (!fs::exists(configFile)) {
    createDefaultConfig();
  }
}

void ConfigManager::createDefaultConfig() {
  toml::table defaultConfig;

  defaultConfig.insert("theme_darkmode", false);
  defaultConfig.insert("exitPopupDontShowAgain", false);
  defaultConfig.insert_or_assign("exitMinimiseToTray", false);

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

void ConfigManager::saveConfig(const toml::table &config) {
  try {
    std::ofstream configFileStream(configFile);
    if (configFileStream) {
      configFileStream << config;
      configFileStream.close();
      std::cout << "Configuration saved successfully to: " << configFile
                << std::endl;
    } else {
      std::cerr << "Failed to open config file for saving: " << configFile
                << std::endl;
    }
  } catch (const std::exception &e) {
    std::cerr << "Error saving config file: " << e.what() << std::endl;
  }
}
