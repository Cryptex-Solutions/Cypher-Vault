#include "Globals.h"

toml::table config = ConfigManager::instance().loadConfig();
ThemeManager &themeManager = ThemeManager::instance();
SvgManager &svgManager = SvgManager::instance();
ConfigManager &configManager = ConfigManager::instance();