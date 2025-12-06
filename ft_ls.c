#include "ft_ls.h"
#include "libft.h"
#include <string.h>
#include <limits.h>
#include <grp.h>
#include <pwd.h>
#include <time.h>

int cmp_normal(const char *str1, const char *str2);

struct options options;
t_list *lst = NULL;
int (*cmp)(const char *, const char *) = cmp_normal;

struct file *file_constructor(const char *file_name,
							  const char *file_rel_path) {
	struct file *file = ft_calloc(1, sizeof(struct file));

	file->name = file_name;
	stat(file_rel_path, &file->stat);
	return (file);
}

void print_dir_l(const size_t filenbr) {
	t_list *tmp = lst;
	struct file *file;

	ft_printf("total %d\n", filenbr);
	for (size_t i = 0; i < filenbr; i++) {
		file = (struct file *)tmp->content;
		print_mode(file->stat.st_mode);
		print_user(file->stat.st_uid);
		print_group(file->stat.st_gid);
		print_size(file->stat.st_size);
		print_time(&file->stat);
		print_name(file->name);
		ft_printf("\n");
		tmp = tmp->next;
	}
}

void print_dir(const size_t filenbr) {
	t_list *tmp = lst;
	struct file *file;

	for (size_t i = 0; i < filenbr; i++) {
		file = (struct file *)tmp->content;
		print_name(file->name);
		tmp = tmp->next;
	}
}

int parser_options(char *option) {
	for (int i = 1; option[i] != '\0'; i++) {
		switch (option[i]) {
		case 'a':
			options.all = true;
			break;
		case 'r':
			cmp = cmp_reverse;
			options.reverse = true;
			break;
		case 'R':
			options.recursive = true;
			break;
		case 'l':
			options.long_list = true;
			break;
		default:
			ft_printf("Option not handled\n");
			break;
		}
	}
	return (0);
}

void swap_node(t_list *node1, t_list *node2) {
	void *tmp = node1->content;

	node1->content = node2->content;
	node2->content = tmp;
}

void sort_files(const size_t filenbr) {
	t_list *curr = lst;

	if (curr == NULL) {
		return ;
	}
	for (size_t i = 0; i < filenbr; i++) {
		t_list *tmp = curr;
		for (size_t k = i; k < filenbr; k++) {
			const struct file *file = (struct file *)tmp->content;
			const struct file *curr_file = (struct file *)curr->content;
			if (cmp(curr_file->name, file->name)) {
				swap_node(curr, tmp);
			}
			tmp = tmp->next;
		}
		curr = curr->next;
	}
}

void get_rel_path(char *dest, char *dir_path, char *file_name) {
	size_t dir_len = ft_strlen(dir_path);

	ft_strlcpy(dest, dir_path, dir_len);
	ft_strlcpy(dest + dir_len, "/", 1);
	ft_strlcpy(dest + dir_len + 1, file_name, ft_strlen(file_name));
}

int ft_ls(char *dir_path) {
	DIR *dirp;
	char *dirs_path[200] = {0};
	char file_rel_path[PATH_MAX];
	struct dirent *dir = NULL;
	size_t filenbr = 0;
	int nbr_dirs = 0;
	t_list *node = lst;

	dirp = opendir(dir_path);
	if (dirp == NULL) {
		perror(dir_path);
		return (1);
	}

	ft_printf("%s:\n", dir_path);

	while ((dir = readdir(dirp)) != NULL) {
		if (options.all == false && dir->d_name[0] == '.') {
			continue;
		}
		get_rel_path(file_rel_path, dir_path, dir->d_name);
		struct file *file = file_constructor(dir->d_name, file_rel_path);
		if (S_ISDIR(file->stat.st_mode)) {
			dirs_path[nbr_dirs++] = ft_strdup(file_rel_path);
		}
		if (node == NULL) {
			node = ft_lstnew(file);
			ft_lstadd_back(&lst, node);
		} else {
			free(node->content);
			node->content = (void *)file;
		}
		filenbr++;
		node = node->next;
	}

	sort_files(filenbr);
	if (options.long_list == true) {
		print_dir_l(filenbr);
	} else {
		print_dir(filenbr);
	}

#if DEBUG
	ft_printf("Closing Dir\n");
	ft_printf("Nbr of dirs: %d\n", nbr_dirs);
	ft_printf("\tMore Dirs: ");
	for (int i = 0; i < nbr_dirs; i++) {
		ft_printf("%s ", dirs_path[i]);
	}
#endif
	closedir(dirp);
	ft_printf("\n");

	if (options.recursive == true) {
		ft_printf("\n");
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

	memset(&options, false, sizeof(struct options));
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
	ft_printf("\tall: %d\n\treverse: %d\n\trecursive: %d\n\tlong_list: %d\n", options.all,
			  options.reverse, options.recursive, options.long_list);
	ft_printf("Finish DEBUG\n\n");
#endif

	int ret;
	for (int i = 0; i < nbr_dirs; i++) {
		ret = ft_ls(dir_paths[i]);
	}

	while (lst != NULL) {
		t_list *tmp = lst;
		lst = lst->next;
		free(tmp->content);
		free(tmp);
	}
	return (ret);
}
