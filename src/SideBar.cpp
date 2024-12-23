#include "SideBar.h"

SideBar::SideBar(QWidget *parent) : QWidget(parent) {
  setObjectName("SideBar");

  panel = new QWidget(this);
}
