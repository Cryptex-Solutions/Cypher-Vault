#include "MainWindow.h"
#include "Globals.h"

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

void MainWindow::closeEvent(QCloseEvent *event) {
  // Save the config file
  configManager.saveConfig(config);

  QMessageBox::StandardButton reply = QMessageBox::question(
      this, "Exit Confirmation", "Are you sure you want to exit?",
      QMessageBox::Yes | QMessageBox::No);

  if (reply == QMessageBox::Yes) {
    // Perform additional cleanup if necessary
    event->accept(); // Allow the window to close
  } else {
    event->ignore(); // Prevent the window from closing
  }
}
