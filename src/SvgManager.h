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
  // Get the singleton instance
  static SvgManager &instance();

  // Load SVGs into memory
  void loadSvg(const QString &name, const QString &svgContent);

  // Get a renderer for an SVG
  QSvgRenderer *getRenderer(const QString &name);

  // Change color groups
  void setColorGroup(const QString &groupName, const QString &color);

  // Group association
  void assignToGroup(const QString &name, const QString &groupName);

  // Return a QIcon from a QSvgRenderer
  QIcon getIcon(const QString &key, const QSize &size = QSize(20, 20));

private:
  // Private constructor for singleton
  SvgManager(QObject *parent = nullptr);
  ~SvgManager() = default;

  SvgManager(const SvgManager &) = delete;            // No copy
  SvgManager &operator=(const SvgManager &) = delete; // No assignment

  QMap<QString, QString> svgContentMap;      // SVGs by name
  QMap<QString, QSvgRenderer *> rendererMap; // Renderers
  QMap<QString, QString> groupColorMap;      // Group colors
  QMap<QString, QString> groupAssignments;   // SVG -> Group
  QMap<QString, QByteArray> svgDataMap;      // Raw SVG data by name
  QMap<QString, QSvgRenderer *>
      svgRenderers; // Stores QSvgRenderer instances by name
};

#endif // SVGMANAGER_H
