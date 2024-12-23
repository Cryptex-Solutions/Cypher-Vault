#include "MainWindow.h"
#include "Globals.h"

#include "ExitConfirmationDialog.h"
#include "QMessageBox"
#include "SideBar.h"
#include <QPushButton>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
  trayManager = new TrayManager(this, this);
  trayManager->showTrayIcon();

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
  config.insert_or_assign("theme_darkmode", toggleDarkMode);
  themeManager.setDarkMode(toggleDarkMode);
  applyTheme();
}

void MainWindow::setupSettings() {
  bool darkMode = config.contains("theme_darkmode")
                      ? config["theme_darkmode"].as_boolean()->get()
                      : false;
  themeManager.setDarkMode(darkMode);
}

void MainWindow::closeEvent(QCloseEvent *event) {
  configManager.saveConfig(config);

  bool dontShowAgainPopup =
      config.contains("exitPopupDontShowAgain")
          ? config["exitPopupDontShowAgain"].as_boolean()->get()
          : false;

  if (dontShowAgainPopup) {
    bool minimiseToTray = config.contains("exitMinimiseToTray")
                              ? config["exitMinimiseToTray"].as_boolean()->get()
                              : false;

    if (minimiseToTray) {
      event->ignore();
      hide();
    } else {
      event->accept();
    }
    return;
  }

  ExitConfirmationDialog dialog(this);

  bool minimiseToTray = (dialog.exec() == QDialog::Accepted);

  if (dialog.neverShowAgain()) {
    config.insert_or_assign("exitPopupDontShowAgain", true);
  }

  config.insert_or_assign("exitMinimiseToTray", minimiseToTray);

  if (minimiseToTray) {
    event->ignore();
    hide();
  } else {
    event->accept();
  }

  configManager.saveConfig(config);
}

void MainWindow::ShowUI() {
  show();
  activateWindow();
}