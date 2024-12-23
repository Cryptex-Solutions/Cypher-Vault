#ifndef TRAYMANAGER_H
#define TRAYMANAGER_H

#include <QMenu>
#include <QObject>
#include <QSystemTrayIcon>

class MainWindow;

class TrayManager : public QObject {
  Q_OBJECT

public:
  explicit TrayManager(MainWindow *mainWindow, QObject *parent = nullptr);
  ~TrayManager();

  void showTrayIcon();

private slots:
  void onShowActionTriggered();
  void onQuitActionTriggered();

private:
  QSystemTrayIcon *trayIcon;
  QMenu *trayMenu;
  QAction *showAction;
  QAction *quitAction;
  MainWindow *mainWindow;
};

#endif // TRAYMANAGER_H
