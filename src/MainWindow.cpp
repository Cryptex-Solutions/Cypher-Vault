#include "MainWindow.h"
#include "ConfigManager.h"
#include "SideBar.h"
#include "SvgManager.h"
#include "ThemeManager.h"
#include <QPushButton>
#include <QVBoxLayout>

ThemeManager &themeManager = ThemeManager::instance();
SvgManager &svgManager = SvgManager::instance();
ConfigManager &configManager = ConfigManager::instance();

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
  setObjectName("MainWindow");
  setupUI();
  setupConnections();

  toml::table config = configManager.loadConfig();

  bool darkMode = config.contains("theme_darkmode")
                      ? config["theme_darkmode"].as_boolean()->get()
                      : false; // Default to false if the config file fucks up
  themeManager.setDarkMode(darkMode);

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

  themeManager.setDarkMode(toggleDarkMode);
  applyTheme();
}