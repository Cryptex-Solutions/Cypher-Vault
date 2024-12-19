#ifndef OS_DETECTOR_H
#define OS_DETECTOR_H

class OSDetector {
public:
  enum class OS { Windows, macOS, Linux, Unix, POSIX, Unknown };

  // Retrieve the detected OS
  static OS getOS() { return detectedOS; }

private:
  // Detect and store the OS at compile-time
  static const OS detectedOS;
};

#endif // OS_DETECTOR_H
