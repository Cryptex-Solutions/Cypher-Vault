#include "MainWindow.h"
#include "Globals.h"

#include "ExitConfirmationDialog.h"
#include "QMessageBox"
#include "SideBar.h"
#include <QPushButton>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
  setObjectName("MainWindow");
  setupUI();
  setupConnections();
  setupSettings();
  applyTheme();
}

MainWindow::~MainWindow() {}

void MainWindow::setupUI() {
  setWindowFlags(Qt::FramelessWindowHint);

  mainLayout = new QVBoxLayout(this);

  titleBar = new TitleBar(this);

  SideBar *sideBar = new SideBar(this);

  mainLayout->addWidget(titleBar);

  mainLayout->addWidget(sideBar);

  QPushButton *toggleButton = new QPushButton("Toggle Dark Mode", this);
  mainLayout->addWidget(toggleButton);

  mainLayout->addStretch();

  mainLayout->setContentsMargins(0, 0, 0, 0);
  mainLayout->setSpacing(0);

  resize(800, 600);

  connect(toggleButton, &QPushButton::clicked, this, &MainWindow::toggleTheme);

  svgManager.setColorGroup("TitleBar", themeManager.getGroupColor("TitleBar"));
}

void MainWindow::setupConnections() {
  connect(titleBar, &TitleBar::minimizeRequested, this,
          &QWidget::showMinimized);
  connect(titleBar, &TitleBar::maximizeRequested, [this]() {
    if (isMaximized()) {
      showNormal();
    } else {
      showMaximized();
    }
  });
  connect(titleBar, &TitleBar::closeRequested, this, &QWidget::close);
}

void MainWindow::applyTheme() {
  setStyleSheet(themeManager.getStyleSheet());
  svgManager.setColorGroup("TitleBar", themeManager.getGroupColor("TitleBar"));
  themeManager.notifyObservers();
}

void MainWindow::toggleTheme() {
  bool toggleDarkMode = !themeManager.isDarkMode();
  // change the config file
  config.insert_or_assign("theme_darkmode", toggleDarkMode);
  // actually change the theme
  themeManager.setDarkMode(toggleDarkMode);
  applyTheme();
}

void MainWindow::setupSettings() {
  // Load Darkmode from file
  bool darkMode = config.contains("theme_darkmode")
                      ? config["theme_darkmode"].as_boolean()->get()
                      : false; // Default to false if the config file breaks
  themeManager.setDarkMode(darkMode);
}

void minimiseToTrayFunction() {
  // TEMP FUNC
}

void MainWindow::closeEvent(QCloseEvent *event) {
  // Save the current configuration
  configManager.saveConfig(config);

  // Check if the "Don't Show Again" option is enabled
  bool dontShowAgainPopup =
      config.contains("exitPopupDontShowAgain")
          ? config["exitPopupDontShowAgain"].as_boolean()->get()
          : false;

  // Handle "Don't Show Again" logic
  if (dontShowAgainPopup) {
    bool minimiseToTray = config.contains("exitMinimiseToTray")
                              ? config["exitMinimiseToTray"].as_boolean()->get()
                              : false;

    if (minimiseToTray) {
      // Minimize to tray
      event->ignore();
      minimiseToTrayFunction();
    } else {
      // Close the application
      event->accept();
    }
    return;
  }

  // Show the exit confirmation dialog
  ExitConfirmationDialog dialog(this);

  // Determine user choice
  bool minimiseToTray = (dialog.exec() == QDialog::Accepted);

  // Check "Never Show Again" option
  if (dialog.neverShowAgain()) {
    config.insert_or_assign("exitPopupDontShowAgain", true);
  }

  // Update minimize/exit preference and act accordingly
  config.insert_or_assign("exitMinimiseToTray", minimiseToTray);

  if (minimiseToTray) {
    event->ignore();
    minimiseToTrayFunction();
  } else {
    event->accept();
  }

  // Save the updated configuration
  configManager.saveConfig(config);
}
