#ifndef _FILEUTIL_H
#define _FILEUTIL_H

#include <string>
#include <stdbool.h>

class FileUtil {
public:
  static bool IsFile(std::string path);
  static bool IsDir(std::string path);
};

#endif // _FILEUTIL_H
