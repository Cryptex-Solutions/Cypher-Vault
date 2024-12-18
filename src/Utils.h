#ifndef UTILS_H
#define UTILS_H

#include "OSDetector.h"
#include <string>

class Utils {
public:
  static std::string getConfigPath();
  static std::string getDependenciesPath();
};

#endif // UTILS_H
