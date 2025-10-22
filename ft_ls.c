#include "libft.h"
#include "ft_ls.h"

struct options options;

int parser_options(char *option) {
	for (int i = 1; option[i] != '\0'; i++) {
		switch (option[i]) {
			case 'a':
				options.all = true;
			break;
			case 'r':
				options.reverse = true;
			break;
			case 'R':
				options.recursive = true;
			break;
			default:
				ft_printf("Option not handled\n");
			break;
		}
	}
	return (0);
}

int ft_ls(char *dir_pathname) {
	DIR *dirp;
	char *dirs_path[50] = {0};
	struct dirent *dir = NULL;

	char *dir_abs_path = ft_strjoin(dir_pathname, "/");
	dirp = opendir(dir_pathname);
	if (dirp == NULL) {
		perror(dir_pathname);
		return (1);
	}

	ft_printf("%s:\n", dir_pathname);

	int nbr_dirs = 0;
	while ((dir = readdir(dirp)) != NULL) {
		char *abs_path = ft_strjoin(dir_abs_path, dir->d_name);
		if (options.all == false && !ft_strncmp(dir->d_name, ".", 1)) {
			continue;
		}
		struct stat buf;
		stat(abs_path, &buf);
		if (S_ISDIR(buf.st_mode)) {
			dirs_path[nbr_dirs++] = abs_path;
		}
		ft_printf("%s ", dir->d_name);
	}
	ft_printf("\n\n");

	#if DEBUG
	ft_printf("Closing Dir\n");
	ft_printf("Nbr of dirs: %d\n", nbr_dirs);
	ft_printf("More Dirs: ");
	for (int i = 0; i < nbr_dirs; i++) {
		ft_printf("%s\n", dirs_path[i]);
	}
	#endif
	closedir(dirp);

	if (options.recursive == true) {
		for (int i = 0; i < nbr_dirs; i++) {
			ft_ls(dirs_path[i]);
		}
	}

	free(dir_abs_path);
	return (0);
}

int main(int argc, char **argv) {
	char *dir_paths[50] = {0};
	int nbr_dirs = 0;

	for (int i = 1; i < argc; i++) {
		char *arg = argv[i];
		if (arg[0] == '-' && arg[1]) {
			parser_options(arg);
		} else {
			dir_paths[nbr_dirs++] = arg;
		}
	}
	if (nbr_dirs == 0) {
		dir_paths[nbr_dirs++] = ".";
	}

	#if DEBUG
	ft_printf("DEBUG Log\n");
	ft_printf("  Active Options:\n");
	ft_printf("\tall: %d\n\treverse: %d\n\trecursive: %d\n", options.all, options.reverse, options.recursive);
	ft_printf("Finish DEBUG\n\n");
	#endif

	for (int i = 0; i < nbr_dirs; i++) {
		ft_ls(dir_paths[i]);
	}
	return (0);
}
