#include "TitleBar.h"
#include "SvgManager.h"
#include "ThemeManager.h"

TitleBar::TitleBar(QWidget *parent) : QWidget(parent), dragPosition(QPoint()) {
  setObjectName("TitleBar");

  panel = new QWidget(this);

  panel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

  titleLabel = new QLabel("Cypher-Vault", this);
  titleLabel->setContentsMargins(5, 5, 5, 5);

  minimizeButton = new QPushButton(this);
  maximizeButton = new QPushButton(this);
  closeButton = new QPushButton(this);

  updateIcons();

  minimizeButton->setIconSize(QSize(25, 25));
  maximizeButton->setIconSize(QSize(25, 25));
  closeButton->setIconSize(QSize(25, 25));

  minimizeButton->setFixedSize(30, 30);
  maximizeButton->setFixedSize(30, 30);
  closeButton->setFixedSize(30, 30);

  QHBoxLayout *layout = new QHBoxLayout(panel);
  layout->addWidget(titleLabel);
  layout->addStretch();
  layout->addWidget(minimizeButton);
  layout->addWidget(maximizeButton);
  layout->addWidget(closeButton);
  layout->setContentsMargins(5, 5, 5, 5);
  layout->setSpacing(5);

  QVBoxLayout *titleBarLayout = new QVBoxLayout(this);
  titleBarLayout->addWidget(panel);
  titleBarLayout->setContentsMargins(0, 0, 0, 0);
  titleBarLayout->setSpacing(0);

  connect(minimizeButton, &QPushButton::clicked, this,
          &TitleBar::minimizeRequested);
  connect(maximizeButton, &QPushButton::clicked, this,
          &TitleBar::maximizeRequested);
  connect(closeButton, &QPushButton::clicked, this, &TitleBar::closeRequested);

  ThemeManager::instance().addObserver([this]() { updateIcons(); });
}

void TitleBar::updateIcons() {
  minimizeButton->setIcon(SvgManager::instance().getIcon("Minus"));
  maximizeButton->setIcon(SvgManager::instance().getIcon("Plus"));
  closeButton->setIcon(SvgManager::instance().getIcon("Close"));
}

void TitleBar::mouseDoubleClickEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    if (parentWidget()->isMaximized()) {
      parentWidget()->showNormal();
    } else {
      parentWidget()->showMaximized();
    }
  }
}

void TitleBar::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    dragPosition =
        event->globalPos() - parentWidget()->frameGeometry().topLeft();
    event->accept();
  }
}

void TitleBar::mouseMoveEvent(QMouseEvent *event) {
  if (event->buttons() & Qt::LeftButton) {
    parentWidget()->move(event->globalPos() - dragPosition);
    event->accept();
  }
}
