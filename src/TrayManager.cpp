#include "TrayManager.h"
#include <QApplication>
#include <QMessageBox>

TrayManager::TrayManager(QObject *parent)
    : QObject(parent), trayIcon(new QSystemTrayIcon(this)),
      trayMenu(new QMenu()) {
  // Create actions
  showAction = new QAction("Show", this);
  quitAction = new QAction("Quit", this);

  // Connect actions to slots
  connect(showAction, &QAction::triggered, this,
          &TrayManager::onShowActionTriggered);
  connect(quitAction, &QAction::triggered, this,
          &TrayManager::onQuitActionTriggered);

  // Add actions to the tray menu
  trayMenu->addAction(showAction);
  trayMenu->addSeparator();
  trayMenu->addAction(quitAction);

  // Configure tray icon
  trayIcon->setContextMenu(trayMenu);
  trayIcon->setIcon(QIcon(":/icons/resources/icon.png"));
  trayIcon->setToolTip("Tray Application");

  connect(trayIcon, &QSystemTrayIcon::activated, this,
          [](QSystemTrayIcon::ActivationReason reason) {
            if (reason == QSystemTrayIcon::Trigger) {
              QMessageBox::information(nullptr, "Tray Icon",
                                       "Tray icon clicked!");
            }
          });
}

TrayManager::~TrayManager() {
  delete trayIcon;
  delete trayMenu;
}

void TrayManager::showTrayIcon() { trayIcon->show(); }

void TrayManager::onShowActionTriggered() {
  QMessageBox::information(nullptr, "Tray Manager", "Show action triggered!");
}

void TrayManager::onQuitActionTriggered() { QApplication::quit(); }
