#include "ThemeManager.h"

ThemeManager &ThemeManager::instance() {
  static ThemeManager instance;
  return instance;
}

ThemeManager::ThemeManager() : darkMode(true) { setupStyleSheets(); }

void ThemeManager::setupStyleSheets() {
  darkStyleSheet = R"(
        #MainWindow {
            background-color: #222;
        }
        #TitleBar QWidget {
            background-color: #3D3D3D;
        }
        #TitleBar QLabel {
            color: #DCDCDC;
        }
        #TitleBar QPushButton {
            background-color: #3D3D3D;
            color: #DCDCDC;
            border: none;
        }
        #TitleBar QPushButton:hover {
            background-color: #555;
        }
        #TitleBar QPushButton:pressed {
            background-color: #666;
        }
        #SideBar QWidget {
            background-color: #FF0000;
        }
    )";

  lightStyleSheet = R"(
        #MainWindow {
            background-color: #FFFFFF;
        }
        #TitleBar QWidget {
            background-color: #E0E0E0;
        }
        #TitleBar QLabel {
            color: #000000;
        }
        #TitleBar QPushButton {
            background-color: #E0E0E0;
            color: #000000;
            border: none;
        }
        #TitleBar QPushButton:hover {
            background-color: #F0F0F0;
        }
        #TitleBar QPushButton:pressed {
            background-color: #C0C0C0;
        }
        #SideBar QWidget {
            background-color: #FF0000;
        }
    )";
}

void ThemeManager::setDarkMode(bool enable) { darkMode = enable; }

bool ThemeManager::isDarkMode() const { return darkMode; }

QString ThemeManager::getStyleSheet() const {
  return darkMode ? darkStyleSheet : lightStyleSheet;
}

QString ThemeManager::getGroupColor(const QString &groupName) const {

  if (darkMode) {
    if (groupName == "TitleBar") {
      return "#7d7d7d";
    } else if (groupName == "Sidebar") {
      return "#BBBBBB";
    } else if (groupName == "Menu") {
      return "#CCCCCC";
    }
  } else {
    if (groupName == "TitleBar") {
      return "#616161";
    } else if (groupName == "Sidebar") {
      return "#333333";
    } else if (groupName == "Menu") {
      return "#444444";
    }
  }
  return "#FFFFFF";
}

void ThemeManager::addObserver(ThemeChangeCallback callback) {
  observers.push_back(callback);
}

void ThemeManager::notifyObservers() {
  for (auto &callback : observers) {
    callback();
  }
}