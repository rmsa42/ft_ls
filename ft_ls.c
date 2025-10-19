#include "libft.h"
#include <dirent.h>
#include "ft_ls.h"

struct options options;

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

int parser_options(char *option) {
	for (int i = 1; option[i] != '\0'; i++) {
		switch (option[i]) {
			case 'a':
				options.all = true;
			break;
			case 'r':
				options.reverse = true;
			break;

			default:
				ft_printf("Option not handled\n");
			break;
		}
	}
	return (0);
}

int parser(int argc, char **args, char **dir_path) {
	for (int i = 1; i < argc; i++) {
		char *arg = args[i];
		ft_printf("Arg: %s\n", arg);
		if (arg[0] == '-' && arg[1]) {
			parser_options(arg);
		} else {
			*dir_path = arg;
		}
	}
	#if DEBUG == 1
	ft_printf("DEBUG Log\n");
	ft_printf("  Dir_Path: %s\n", *dir_path);
	ft_printf("  Active Options:\n");
	ft_printf("\tall: %d\n\treverse: %d\n", options.all, options.reverse);
	ft_printf("Finish DEBUG\n\n");
	#endif
	return (0);
}

int main(int argc, char **argv) {
	char *dir_path = ".";
	DIR *dirp;

	parser(argc, argv, &dir_path);

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
