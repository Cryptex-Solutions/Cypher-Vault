#include "ThemeManager.h"
#include <iostream>

// Singleton instance
ThemeManager &ThemeManager::instance() {
  static ThemeManager instance;
  return instance;
}

// Private constructor
ThemeManager::ThemeManager() : darkMode(true) {
  setupStyleSheets();
  notifyObservers();
}

void ThemeManager::setupStyleSheets() {
  // Dark Style Sheet
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
    )";

  // Light Style Sheet
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
    )";
}

void ThemeManager::setDarkMode(bool enable) {
  darkMode = enable;
  notifyObservers();
}

bool ThemeManager::isDarkMode() const { return darkMode; }

QString ThemeManager::getStyleSheet() const {
  return darkMode ? darkStyleSheet : lightStyleSheet;
}

QString ThemeManager::getGroupColor(const QString &groupName) const {
  std::cout << "Dark Mode: " << darkMode << std::endl;
  if (darkMode) {
    if (groupName == "TitleBar") {
      std::cout << "dark " << std::endl;
      return "#FF0000";
    } else if (groupName == "Sidebar") {
      return "#BBBBBB";
    } else if (groupName == "Menu") {
      return "#CCCCCC";
    }
  } else {
    if (groupName == "TitleBar") {
      std::cout << "light " << std::endl;
      return "#00FF00";
    } else if (groupName == "Sidebar") {
      return "#333333";
    } else if (groupName == "Menu") {
      return "#444444";
    }
  }
  return "#FFFFFF"; // Default color
}

void ThemeManager::addObserver(ThemeChangeCallback callback) {
  observers.push_back(callback);
}

void ThemeManager::notifyObservers() {
  for (auto &callback : observers) {
    callback();
  }
}