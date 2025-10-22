#ifndef FT_LS_H
#define FT_LS_H

#include <stdbool.h>
#include <dirent.h>
#include <sys/stat.h>

struct options {
	bool all;
	bool reverse;
	bool recursive;
};

#endif
