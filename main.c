#include "libft.h"
#include <dirent.h>

void print_dir(DIR *dirp) {
	struct dirent *dir = NULL;

	while ((dir = readdir(dirp)) != NULL) {
		ft_printf("%s\n", dir->d_name);
	}
}

int main(int argc, char **argv) {
	char *dir_path;
	DIR *dirp;

	if (argc > 1) {
		dir_path = argv[1];
	} else {
		dir_path = ".";
	}

	dirp = opendir(dir_path);

	print_dir(dirp);
	return (0);
}
