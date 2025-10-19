#include "libft.h"
#include <dirent.h>

#define DEBUG 1

void print_dir(DIR *dirp) {
	struct dirent *dir = NULL;

	#if DEBUG == 1
	ft_printf("Listing Dir:\n");
	#endif
	dir = readdir(dirp);
	ft_printf("%s", dir->d_name);
	while ((dir = readdir(dirp)) != NULL) {
		ft_printf(" %s", dir->d_name);
	}
	ft_printf("\n");
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
	#if DEBUG == 1
	ft_printf("Opened Dir\n");
	#endif

	print_dir(dirp);

	#if DEBUG == 1
	ft_printf("Closing Dir\n");
	#endif
	closedir(dirp);
	return (0);
}
