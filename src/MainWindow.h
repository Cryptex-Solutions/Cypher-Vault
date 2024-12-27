#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "SideBar.h"
#include "TitleBar.h"
#include "TrayManager.h"
#include <QVBoxLayout>
#include <QWidget>

class MainWindow : public QWidget {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  void ShowUI();

protected:
  void closeEvent(QCloseEvent *event) override;

private:
  QVBoxLayout *mainLayout;
  TitleBar *titleBar;
  TrayManager *trayManager;
  SideBar *sideBar;

  void setupUI();
  void setupConnections();
  void setupSettings();
  void toggleTheme();
  void applyTheme();
};

#endif // MAINWINDOW_H
