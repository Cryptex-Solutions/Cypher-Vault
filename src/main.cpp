#include "MainWindow.h"
#include "OSDetector.h"
#include "SvgIcons.h"
#include "SvgManager.h"
#include <QApplication>
#include <iostream>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

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

  OSDetector::OS os = OSDetector::getOS();

  if (os == OSDetector::OS::Windows) {
    std::cout << "The operating system is Windows." << std::endl;
  } else if (os == OSDetector::OS::macOS) {
    std::cout << "The operating system is macOS." << std::endl;
  } else if (os == OSDetector::OS::Linux) {
    std::cout << "The operating system is Linux." << std::endl;
  } else {
    std::cout << "The operating system is unsupported" << std::endl;
  }

  return app.exec();
}

// testing change
