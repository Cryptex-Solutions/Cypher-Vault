#ifndef THEMEMANAGER_H
#define THEMEMANAGER_H

#include <QPalette>
#include <QString>
#include <functional>
#include <vector>

class ThemeManager {
public:
  // Singleton instance accessor
  static ThemeManager &instance();

  // Setters
  void setDarkMode(bool enable);
  bool isDarkMode() const;

  QString getGroupColor(const QString &groupName) const;

  // Getters
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
