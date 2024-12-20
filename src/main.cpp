#include "Globals.h"
#include "MainWindow.h"
#include "SvgIcons.h"
#include <QApplication>
#include <cstdlib>
int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  // Load Config file
  configManager.loadConfig();

  // Load icons into SvgManager
  svgManager.loadSvg("Minus", SvgIcons::TitleIconMinus);
  svgManager.loadSvg("Plus", SvgIcons::TitleIconPlus);
  svgManager.loadSvg("Close", SvgIcons::TitleIconClose);

  // Assign icons to the "TitleBar" group
  svgManager.assignToGroup("Minus", "TitleBar");
  svgManager.assignToGroup("Plus", "TitleBar");
  svgManager.assignToGroup("Close", "TitleBar");

  // This initialises Window on run
  MainWindow mainWindow;
  mainWindow.show();
  mainWindow.setWindowIcon(
      QIcon(":/icon.ico")); // Ensure the icon is included in your resources

  return app.exec();
}

// testing change
