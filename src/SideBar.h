#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QWidget>

class SideBar : public QWidget {
  Q_OBJECT

public:
  explicit SideBar(QWidget *parent = nullptr);

private:
  QWidget *panel;
};

#endif // SIDEBAR_H
