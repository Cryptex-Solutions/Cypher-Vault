#include "TitleBar.h"
#include "SvgManager.h"
#include "ThemeManager.h"
#include <iostream>

TitleBar::TitleBar(QWidget *parent) : QWidget(parent), dragPosition(QPoint()) {
  setObjectName("TitleBar");

  // Create the title bar panel widget
  panel = new QWidget(this);
  panel->setObjectName("TitleBarPanel");

  panel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

  // Create title bar components
  titleLabel = new QLabel("Cypher-Vault", this);
  titleLabel->setObjectName("TitleBarTitle");

  minimizeButton = new QPushButton(this);
  maximizeButton = new QPushButton(this);
  closeButton = new QPushButton(this);

  // Initial icons
  updateIcons();

  // Set button sizes
  minimizeButton->setIconSize(QSize(25, 25));
  maximizeButton->setIconSize(QSize(25, 25));
  closeButton->setIconSize(QSize(25, 25));

  minimizeButton->setFixedSize(30, 30);
  maximizeButton->setFixedSize(30, 30);
  closeButton->setFixedSize(30, 30);

  // Create layout
  QHBoxLayout *layout = new QHBoxLayout(panel);
  layout->addWidget(titleLabel);
  layout->addStretch();
  layout->addWidget(minimizeButton);
  layout->addWidget(maximizeButton);
  layout->addWidget(closeButton);
  layout->setContentsMargins(5, 5, 5, 5);
  layout->setSpacing(5);

  // Add the panel to the main layout of TitleBar
  QVBoxLayout *titleBarLayout = new QVBoxLayout(this);
  titleBarLayout->addWidget(panel);
  titleBarLayout->setContentsMargins(0, 0, 0, 0);
  titleBarLayout->setSpacing(0);

  // Connect signals
  connect(minimizeButton, &QPushButton::clicked, this,
          &TitleBar::minimizeRequested);
  connect(maximizeButton, &QPushButton::clicked, this,
          &TitleBar::maximizeRequested);
  connect(closeButton, &QPushButton::clicked, this, &TitleBar::closeRequested);

  // Register observer for theme changes
  ThemeManager::instance().addObserver([this]() { updateIcons(); });
}

void TitleBar::updateIcons() {
  minimizeButton->setIcon(SvgManager::instance().getIcon("Minus"));
  maximizeButton->setIcon(SvgManager::instance().getIcon("Plus"));
  closeButton->setIcon(SvgManager::instance().getIcon("Close"));
}

// Override mouseDoubleClickEvent to toggle maximize/restore
void TitleBar::mouseDoubleClickEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    // Check if the window is already maximized
    if (parentWidget()->isMaximized()) {
      parentWidget()->showNormal(); // Restore the window to its previous size
    } else {
      parentWidget()->showMaximized(); // Maximize the window
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
  std::cout << "Active" << std::endl;
  if (event->buttons() & Qt::LeftButton) {
    parentWidget()->move(event->globalPos() - dragPosition);
    event->accept();
  }
}
