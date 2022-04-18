#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string>
#include <stdbool.h>

#include "fileutil.h"

bool IsFile(std::string path) {
	struct stat buf;

	int err = stat(path.c_str(), &buf);
	if(-1 == err) {
		return false;
	}

	return S_ISREG(buf.st_mode) == 1;
}

bool IsDir(std::string path) {
	struct stat buf;

	int err = stat(path.c_str(), &buf);
	if(-1 == err) {
		return false;
	}

	return S_ISDIR(buf.st_mode) == 1;
}
