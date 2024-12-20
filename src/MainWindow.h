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

protected:
  void closeEvent(QCloseEvent *event) override;

private:
  QVBoxLayout *mainLayout;
  TitleBar *titleBar;

  void setupUI();
  void setupConnections();
  void setupSettings();
  void toggleTheme();
  void applyTheme();
};

#endif // MAINWINDOW_H
