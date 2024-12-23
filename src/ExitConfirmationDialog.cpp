#include "ExitConfirmationDialog.h"

ExitConfirmationDialog::ExitConfirmationDialog(QWidget *parent)
    : QDialog(parent) {

  setWindowTitle("Exit Confirmation");
  setModal(true);
  setFixedSize(300, 150);

  messageLabel = new QLabel(
      "Would you like to minimize to tray or close the application?", this);
  minimizeButton = new QPushButton("Minimize", this);
  closeButton = new QPushButton("Close", this);
  neverShowAgainCheckBox = new QCheckBox("Never show this popup again?", this);

  mainLayout = new QVBoxLayout(this);
  mainLayout->addWidget(messageLabel);
  mainLayout->addWidget(neverShowAgainCheckBox);

  QHBoxLayout *buttonLayout = new QHBoxLayout();
  buttonLayout->addWidget(minimizeButton);
  buttonLayout->addWidget(closeButton);
  mainLayout->addLayout(buttonLayout);

  connect(minimizeButton, &QPushButton::clicked, this, [this]() { accept(); });
  connect(closeButton, &QPushButton::clicked, this, [this]() { reject(); });
}

bool ExitConfirmationDialog::neverShowAgain() const {
  return neverShowAgainCheckBox->isChecked();
}
