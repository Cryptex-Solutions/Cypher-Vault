#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QHBoxLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QPushButton>
#include <QWidget>

class TitleBar : public QWidget {
  Q_OBJECT

public:
  explicit TitleBar(QWidget *parent = nullptr);

  void updateIcons();

signals:
  void minimizeRequested();
  void maximizeRequested();
  void closeRequested();

protected:
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mouseDoubleClickEvent(QMouseEvent *event) override;

private:
  QLabel *titleLabel;
  QWidget *panel;
  QPushButton *minimizeButton;
  QPushButton *maximizeButton;
  QPushButton *closeButton;
  QPoint dragPosition;
};

#endif // TITLEBAR_H
