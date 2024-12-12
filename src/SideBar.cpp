#include "SideBar.h"

SideBar::SideBar(QWidget *parent) : QWidget(parent) {
  setObjectName("SideBar");

  // Create the side bar panel widget
  panel = new QWidget(this);
}
