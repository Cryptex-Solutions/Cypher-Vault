#include "Globals.h"
#include "MainWindow.h"
#include "SvgIcons.h"
#include "TrayManager.h"
#include <QApplication>
#include <cstdlib>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  // Set the application icon
  app.setWindowIcon(QIcon(":/icons/resources/icon.png"));

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
  mainWindow.setWindowIcon(QIcon(":/icons/resources/icon.png"));
  mainWindow.show();

  TrayManager trayManager;
  trayManager.showTrayIcon();

  return app.exec();
}

// testing change
