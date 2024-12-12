#include "MainContentPage.h"
#include <QLabel>
#include <QVBoxLayout>

MainContentPage::MainContentPage(QWidget *parent) : QWidget(parent) {
  QVBoxLayout *layout = new QVBoxLayout(this);
  QLabel *label = new QLabel("Main Content Page", this);
  layout->addWidget(label);
  setLayout(layout);
}

//testing
