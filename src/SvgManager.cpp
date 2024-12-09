#include "SvgManager.h"
#include "ThemeManager.h"
#include <QRegularExpression>
#include <qnamespace.h>

// Singleton instance
SvgManager &SvgManager::instance() {
  static SvgManager instance;
  return instance;
}

SvgManager::SvgManager(QObject *parent) : QObject(parent) {}

void SvgManager::loadSvg(const QString &name, const QString &svgContent) {
  if (!rendererMap.contains(name)) {
    // Store the raw SVG content in svgContentMap
    svgContentMap[name] = svgContent;

    // Store the raw SVG data in svgDataMap
    svgDataMap[name] = svgContent.toUtf8();

    // Create and store the renderer for this SVG
    QSvgRenderer *renderer = new QSvgRenderer(svgContent.toUtf8(), this);
    rendererMap[name] = renderer;

    // Store the renderer in svgRenderers as well
    svgRenderers[name] = renderer;
  }
}

QSvgRenderer *SvgManager::getRenderer(const QString &name) {
  return rendererMap.value(name, nullptr);
}

void SvgManager::setColorGroup(const QString &groupName, const QString &color) {
  // Get the color for the current theme from ThemeManager
  ThemeManager &themeManager = ThemeManager::instance();
  QString themeColor = themeManager.getGroupColor(groupName);

  // If no color is provided, use the default color
  if (color.isEmpty()) {
    themeColor = "";
  }

  groupColorMap[groupName] = color;

  // Loop through all items in the group and update their colors
  for (auto it = groupAssignments.begin(); it != groupAssignments.end(); ++it) {
    if (it.value() == groupName) {
      const QString &key = it.key();
      if (svgDataMap.contains(key)) {
        QByteArray svgData = svgDataMap[key];

        // Update the fill color in the SVG XML data
        QString svgString = QString::fromUtf8(svgData);
        svgString.replace(QRegularExpression("fill=\"([^\"]*)\""),
                          QString("fill=\"%1\"").arg(color));

        // Update the modified SVG data in svgDataMap
        svgDataMap[key] = svgString.toUtf8();

        // Update the renderer with the modified SVG data
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
