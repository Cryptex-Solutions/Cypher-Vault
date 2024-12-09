#include "SettingsPage.h"
#include <QLabel>
#include <QVBoxLayout>

SettingsPage::SettingsPage(QWidget *parent) : QWidget(parent) {
  QVBoxLayout *layout = new QVBoxLayout(this);
  QLabel *label = new QLabel("Settings Page", this);
  layout->addWidget(label);
  setLayout(layout);
}
