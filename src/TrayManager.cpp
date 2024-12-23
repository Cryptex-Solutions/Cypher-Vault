#include "TrayManager.h"
#include "MainWindow.h"
#include <QApplication>
#include <iostream>

TrayManager::TrayManager(MainWindow *mainWindow, QObject *parent)
    : QObject(parent), trayIcon(new QSystemTrayIcon(this)),
      trayMenu(new QMenu()), mainWindow(mainWindow) {
  // Create actions
  showAction = new QAction("Show", this);
  quitAction = new QAction("Quit", this);

  // Connect actions to slots
  connect(showAction, &QAction::triggered, this,
          &TrayManager::onShowActionTriggered);
  connect(quitAction, &QAction::triggered, this,
          &TrayManager::onQuitActionTriggered);

  // Connect tray icon activation (double click) to onShowActionTriggered
  connect(trayIcon, &QSystemTrayIcon::activated, this,
          [this](QSystemTrayIcon::ActivationReason reason) {
            if (reason == QSystemTrayIcon::Trigger) {
              onShowActionTriggered();
            }
          });

  // Add actions to the tray menu
  trayMenu->addAction(showAction);
  trayMenu->addSeparator();
  trayMenu->addAction(quitAction);

  // Configure tray icon
  trayIcon->setContextMenu(trayMenu);
  trayIcon->setIcon(QIcon(":/icons/resources/icon.png"));
  trayIcon->setToolTip("Tray Application");
}

TrayManager::~TrayManager() {
  delete trayIcon;
  delete trayMenu;
}

void TrayManager::showTrayIcon() { trayIcon->show(); }

void TrayManager::onShowActionTriggered() {
  if (mainWindow) {
    mainWindow->ShowUI();
  } else {
    std::cerr << "MainWindow reference is null" << std::endl;
  }
}

void TrayManager::onQuitActionTriggered() { QApplication::quit(); }
