#include "SideBar.h"

SideBar::SideBar(QWidget *parent) : QWidget(parent) {
  setObjectName("SideBar");

  layout = new QVBoxLayout(this);
  layout->setContentsMargins(0, 0, 0, 0);
  layout->setSpacing(0);

  layout->setAlignment(Qt::AlignTop);

  accountsButton = new QPushButton("Accounts", this);

  settingsButton = new QPushButton("Settings", this);

  layout->addWidget(accountsButton);
  layout->addWidget(settingsButton);

  setLayout(layout);
}
