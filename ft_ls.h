#ifndef FT_LS_H
#define FT_LS_H

#include <stdbool.h>
#include <dirent.h>
#include <sys/stat.h>
#include <linux/limits.h>

struct options {
	bool all;
	bool reverse;
	bool recursive;
	bool long_list;
};

struct file {
	const char *name;
	struct stat stat;
};

int cmp_reverse(const char *str1, const char *str2);
int cmp_normal(const char *str1, const char *str2);
char *stack_trim(char *str);

#endif
