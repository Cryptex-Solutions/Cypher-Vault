#include "SvgManager.h"
#include "ThemeManager.h"
#include <QRegularExpression>
#include <qnamespace.h>

SvgManager &SvgManager::instance() {
  static SvgManager instance;
  return instance;
}

SvgManager::SvgManager(QObject *parent) : QObject(parent) {}

void SvgManager::loadSvg(const QString &name, const QString &svgContent) {
  if (!rendererMap.contains(name)) {
    svgContentMap[name] = svgContent;

    svgDataMap[name] = svgContent.toUtf8();

    QSvgRenderer *renderer = new QSvgRenderer(svgContent.toUtf8(), this);
    rendererMap[name] = renderer;

    svgRenderers[name] = renderer;
  }
}

QSvgRenderer *SvgManager::getRenderer(const QString &name) {
  return rendererMap.value(name, nullptr);
}

void SvgManager::setColorGroup(const QString &groupName, const QString &color) {
  ThemeManager &themeManager = ThemeManager::instance();
  QString themeColor = themeManager.getGroupColor(groupName);

  if (color.isEmpty()) {
    themeColor = "";
  }

  groupColorMap[groupName] = color;

  for (auto it = groupAssignments.begin(); it != groupAssignments.end(); ++it) {
    if (it.value() == groupName) {
      const QString &key = it.key();
      if (svgDataMap.contains(key)) {
        QByteArray svgData = svgDataMap[key];

        QString svgString = QString::fromUtf8(svgData);
        svgString.replace(QRegularExpression("fill=\"([^\"]*)\""),
                          QString("fill=\"%1\"").arg(color));

        svgDataMap[key] = svgString.toUtf8();

        QSvgRenderer *renderer = svgRenderers[key];
        renderer->load(svgDataMap[key]);
      }
    }
  }
}

void SvgManager::assignToGroup(const QString &name, const QString &groupName) {
  groupAssignments[name] = groupName;
}

QIcon SvgManager::getIcon(const QString &key, const QSize &size) {
  QSvgRenderer *renderer = getRenderer(key);
  if (!renderer) {
    return QIcon(); // Return an empty icon if the renderer is not found
  }

  QPixmap pixmap(size);
  pixmap.fill(Qt::transparent);
  QPainter painter(&pixmap);
  renderer->render(&painter);
  return QIcon(pixmap);
}
