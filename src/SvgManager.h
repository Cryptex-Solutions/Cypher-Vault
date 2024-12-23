#ifndef SVGMANAGER_H
#define SVGMANAGER_H

#include <QIcon>
#include <QMap>
#include <QObject>
#include <QPainter>
#include <QString>
#include <QSvgRenderer>

class SvgManager : public QObject {
  Q_OBJECT

public:
  static SvgManager &instance();

  void loadSvg(const QString &name, const QString &svgContent);

  QSvgRenderer *getRenderer(const QString &name);

  void setColorGroup(const QString &groupName, const QString &color);

  void assignToGroup(const QString &name, const QString &groupName);

  QIcon getIcon(const QString &key, const QSize &size = QSize(20, 20));

private:
  SvgManager(QObject *parent = nullptr);
  ~SvgManager() = default;

  SvgManager(const SvgManager &) = delete;
  SvgManager &operator=(const SvgManager &) = delete;

  QMap<QString, QString> svgContentMap;
  QMap<QString, QSvgRenderer *> rendererMap;
  QMap<QString, QString> groupColorMap;
  QMap<QString, QString> groupAssignments;
  QMap<QString, QByteArray> svgDataMap;
  QMap<QString, QSvgRenderer *> svgRenderers;
};

#endif // SVGMANAGER_H
