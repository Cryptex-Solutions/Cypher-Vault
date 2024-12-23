#ifndef GLOBALS_H
#define GLOBALS_H

#include "ConfigManager.h"
#include "SvgManager.h"
#include "ThemeManager.h"
#include <toml.h>

extern toml::table config;
extern ThemeManager &themeManager;
extern SvgManager &svgManager;
extern ConfigManager &configManager;

#endif // GLOBALS_H
