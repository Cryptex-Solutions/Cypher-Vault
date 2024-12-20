#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <string>
#include <toml.hpp>

class ConfigManager {
public:
  ConfigManager();

  // Loads the configuration into a TOML table
  toml::table loadConfig();

  static ConfigManager &instance();
  void saveConfig(const toml::table &config);

private:
  std::string configPath;
  std::string configFile;
  void createDefaultConfig();
};

#endif // CONFIGMANAGER_H
