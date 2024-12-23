#ifndef THEMEMANAGER_H
#define THEMEMANAGER_H

#include <QPalette>
#include <QString>
#include <functional>

class ThemeManager {
public:
  static ThemeManager &instance();

  void setDarkMode(bool enable);
  bool isDarkMode() const;

  QString getGroupColor(const QString &groupName) const;

  QPalette getPalette() const;
  QString getStyleSheet() const;

  // Observer pattern
  using ThemeChangeCallback = std::function<void()>;
  void addObserver(ThemeChangeCallback callback);
  void notifyObservers();

private:
  // Private constructor for singleton
  ThemeManager();
  ~ThemeManager() = default;

  // Delete copy constructor and assignment operator
  ThemeManager(const ThemeManager &) = delete;
  ThemeManager &operator=(const ThemeManager &) = delete;

  bool darkMode;
  QString darkStyleSheet;
  QString lightStyleSheet;
  std::vector<ThemeChangeCallback> observers;

  void setupStyleSheets();
};

#endif // THEMEMANAGER_H
