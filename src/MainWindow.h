#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "TitleBar.h"
#include <QVBoxLayout>
#include <QWidget>

class MainWindow : public QWidget {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  void applyTheme();

private:
  QVBoxLayout *mainLayout;
  TitleBar *titleBar;

  void setupUI();
  void setupConnections();
  void toggleTheme();
};

#endif // MAINWINDOW_H
