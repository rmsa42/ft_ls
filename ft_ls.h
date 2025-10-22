#ifndef FT_LS_H
#define FT_LS_H

#include <stdbool.h>
#include <dirent.h>
#include <sys/stat.h>

#define DEBUG 1

struct options {
	bool all;
	bool reverse;
	bool recursive;
};

#endif
