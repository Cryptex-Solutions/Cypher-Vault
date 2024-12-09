#include "MainWindow.h"
#include "SvgManager.h"
#include "ThemeManager.h"
#include <QPushButton>
#include <QVBoxLayout>

ThemeManager &themeManager = ThemeManager::instance();
SvgManager &svgManager = SvgManager::instance();

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
  setObjectName("MainWindow");
  setupUI();
  setupConnections();

  // Apply default theme
  applyTheme();
}

MainWindow::~MainWindow() {}

void MainWindow::setupUI() {
  // Remove default window title bar
  setWindowFlags(Qt::FramelessWindowHint);

  // Create layouts
  mainLayout = new QVBoxLayout(this);

  // Create custom title bar
  titleBar = new TitleBar(this);

  // Add title bar and placeholder for main content
  mainLayout->addWidget(titleBar);

  // Add a button for toggling dark mode (for testing)
  QPushButton *toggleButton = new QPushButton("Toggle Dark Mode", this);
  mainLayout->addWidget(toggleButton);

  // Set layout
  mainLayout->addStretch(); // Placeholder for main content

  // Set margins and spacing
  mainLayout->setContentsMargins(0, 0, 0, 0);
  mainLayout->setSpacing(0);

  // Set window size
  resize(800, 600);

  // Connect the toggle button to the toggleTheme slot
  connect(toggleButton, &QPushButton::clicked, this, &MainWindow::toggleTheme);
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

  // Update icon colors for the current theme
  svgManager.setColorGroup("TitleBar", themeManager.getGroupColor("TitleBar"));
}

void MainWindow::toggleTheme() {
  themeManager.setDarkMode(!themeManager.isDarkMode());
  applyTheme();
}
