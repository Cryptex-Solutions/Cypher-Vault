#include "ExitConfirmationDialog.h"

ExitConfirmationDialog::ExitConfirmationDialog(QWidget *parent)
    : QDialog(parent) {
  // Set dialog properties
  setWindowTitle("Exit Confirmation");
  setModal(true);
  setFixedSize(300, 150);

  // Create widgets
  messageLabel = new QLabel(
      "Would you like to minimize to tray or close the application?", this);
  minimizeButton = new QPushButton("Minimize", this);
  closeButton = new QPushButton("Close", this);
  neverShowAgainCheckBox = new QCheckBox("Never show this popup again?", this);

  // Layout setup
  mainLayout = new QVBoxLayout(this);
  mainLayout->addWidget(messageLabel);
  mainLayout->addWidget(neverShowAgainCheckBox);

  // Add buttons in a horizontal layout
  QHBoxLayout *buttonLayout = new QHBoxLayout();
  buttonLayout->addWidget(minimizeButton);
  buttonLayout->addWidget(closeButton);
  mainLayout->addLayout(buttonLayout);

  // Connect buttons
  connect(minimizeButton, &QPushButton::clicked, this, [this]() {
    accept(); // Signal dialog acceptance
  });
  connect(closeButton, &QPushButton::clicked, this, [this]() {
    reject(); // Signal dialog rejection
  });
}

bool ExitConfirmationDialog::neverShowAgain() const {
  return neverShowAgainCheckBox->isChecked();
}
