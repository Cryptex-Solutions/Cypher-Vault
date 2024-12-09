#include "MainWindow.h"
#include "SvgIcons.h"
#include "SvgManager.h"
#include "ThemeManager.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  // This is a new change!
  ThemeManager &themeManager = ThemeManager::instance();

  themeManager.setDarkMode(true);

  // Load icons into SvgManager
  SvgManager::instance().loadSvg("Minus", SvgIcons::TitleIconMinus);
  SvgManager::instance().loadSvg("Plus", SvgIcons::TitleIconPlus);
  SvgManager::instance().loadSvg("Close", SvgIcons::TitleIconClose);

  // Assign icons to the "TitleBar" group
  SvgManager::instance().assignToGroup("Minus", "TitleBar");
  SvgManager::instance().assignToGroup("Plus", "TitleBar");
  SvgManager::instance().assignToGroup("Close", "TitleBar");

  MainWindow mainWindow;
  mainWindow.show();

  return app.exec();
}
