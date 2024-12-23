#include "Globals.h"
#include "MainWindow.h"
#include "SvgIcons.h"
#include <QApplication>
#include <cstdlib>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  configManager.loadConfig();

  svgManager.loadSvg("Minus", SvgIcons::TitleIconMinus);
  svgManager.loadSvg("Plus", SvgIcons::TitleIconPlus);
  svgManager.loadSvg("Close", SvgIcons::TitleIconClose);

  svgManager.assignToGroup("Minus", "TitleBar");
  svgManager.assignToGroup("Plus", "TitleBar");
  svgManager.assignToGroup("Close", "TitleBar");

  MainWindow mainWindow;
  mainWindow.show();

  return app.exec();
}
