#ifndef EXITCONFIRMATIONDIALOG_H
#define EXITCONFIRMATIONDIALOG_H

#include <QCheckBox>
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

class ExitConfirmationDialog : public QDialog {
  Q_OBJECT

public:
  explicit ExitConfirmationDialog(QWidget *parent = nullptr);
  bool neverShowAgain() const;

private:
  QLabel *messageLabel;
  QPushButton *minimizeButton;
  QPushButton *closeButton;
  QCheckBox *neverShowAgainCheckBox;
  QVBoxLayout *mainLayout;
};

#endif // EXITCONFIRMATIONDIALOG_H
