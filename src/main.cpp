#include "ConfigManager.h"
#include "MainWindow.h"
#include "SvgIcons.h"
#include "SvgManager.h"
#include "Utils.h"
#include <QApplication>
#include <cstdlib>
#include <iostream>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  // Load config file
  ConfigManager::instance().loadConfig();

  ConfigManager config;
  config.loadConfig();

  // Load icons into SvgManager
  SvgManager::instance().loadSvg("Minus", SvgIcons::TitleIconMinus);
  SvgManager::instance().loadSvg("Plus", SvgIcons::TitleIconPlus);
  SvgManager::instance().loadSvg("Close", SvgIcons::TitleIconClose);

  // Assign icons to the "TitleBar" group
  SvgManager::instance().assignToGroup("Minus", "TitleBar");
  SvgManager::instance().assignToGroup("Plus", "TitleBar");
  SvgManager::instance().assignToGroup("Close", "TitleBar");

  // This initialises Window on run
  MainWindow mainWindow;
  mainWindow.show();
  mainWindow.setWindowIcon(
      QIcon(":/icon.ico")); // Ensure the icon is included in your resources

  // Test path shit
  std::cout << Utils::getConfigPath() << std::endl;
  std::cout << Utils::getDependenciesPath() << std::endl;

  return app.exec();
}

// testing change
