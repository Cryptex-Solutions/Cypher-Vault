#ifndef TRAYMANAGER_H
#define TRAYMANAGER_H

#include <QAction>
#include <QMenu>
#include <QObject>
#include <QSystemTrayIcon>

class TrayManager : public QObject {
  Q_OBJECT

public:
  explicit TrayManager(QObject *parent = nullptr);
  ~TrayManager();

  void showTrayIcon();

private:
  QSystemTrayIcon *trayIcon;
  QMenu *trayMenu;

  QAction *showAction;
  QAction *quitAction;

private slots:
  void onShowActionTriggered();
  void onQuitActionTriggered();
};

#endif // TRAYMANAGER_H
