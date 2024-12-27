#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

class SideBar : public QWidget {
  Q_OBJECT

public:
  explicit SideBar(QWidget *parent = nullptr);

private:
  QWidget *panel;
  QVBoxLayout *layout;
  QPushButton *accountsButton;
  QPushButton *settingsButton;
};

#endif // SIDEBAR_H
