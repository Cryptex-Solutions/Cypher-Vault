#ifndef OS_DETECTOR_H
#define OS_DETECTOR_H

class OSDetector {
public:
  enum class OS { Windows, macOS, Linux, Unix, POSIX, Unknown };

  static OS getOS() { return detectedOS; }

private:
  static const OS detectedOS;
};

#endif // OS_DETECTOR_H
