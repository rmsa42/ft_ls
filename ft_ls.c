#include "libft.h"
#include "ft_ls.h"

struct options options;
t_list *list = NULL;

struct file *file_constructor(const char *file_name, const char *file_rel_path) {
	struct file *file = ft_calloc(1, sizeof(struct file));
	
	file->name = file_name;
	stat(file_rel_path, &file->stat);
	return (file);
}

void print_file(struct file *file) {
	ft_printf("%s ", file->name);
}

void print_dir() {
	while (list != NULL) {
		print_file((struct file *)list->content);
		list = list->next;
	}
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

	dirp = opendir(dir_pathname);
	if (dirp == NULL) {
		perror(dir_pathname);
		return (1);
	}

	ft_printf("%s:\n", dir_pathname);

	int nbr_dirs = 0;
	char *dir_slashed_path = ft_strjoin(dir_pathname, "/");
	t_list *node;
	while ((dir = readdir(dirp)) != NULL) {
		if (options.all == false && dir->d_name[0] == '.') {
			continue;
		}
		char *file_rel_path = ft_strjoin(dir_slashed_path, dir->d_name);
		struct file *file = file_constructor(dir->d_name, file_rel_path);
		if (S_ISDIR(file->stat.st_mode)) {
			dirs_path[nbr_dirs++] = ft_strdup(file_rel_path);
		}
		node = ft_lstnew(file);
		ft_lstadd_back(&list, node);
		free(file_rel_path);
	}

	print_dir();

	#if DEBUG
	ft_printf("Closing Dir\n");
	ft_printf("Nbr of dirs: %d\n", nbr_dirs);
	ft_printf("More Dirs: ");
	for (int i = 0; i < nbr_dirs; i++) {
		ft_printf("%s\n", dirs_path[i]);
	}
	#endif
	closedir(dirp);
	free(dir_slashed_path);
	ft_printf("\n");

	if (options.recursive == true) {
		for (int i = 0; i < nbr_dirs; i++) {
			ft_ls(dirs_path[i]);
			free(dirs_path[i]);
		}
	} else {
		for (int i = 0; i < nbr_dirs; i++) {
			free(dirs_path[i]);
		}
	}

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
