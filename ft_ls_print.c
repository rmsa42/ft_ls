#include "ft_ls.h"
#include "libft.h"
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <stdint.h>
#include <string.h>

void print_name(const char *file_name) {
	ft_printf("%s ", file_name);
}

void print_group(gid_t gid) {
	struct group *group = getgrgid(gid);
	ft_printf("%s ", group->gr_name);
}

void print_user(uid_t uid) {
	struct passwd *pw = getpwuid(uid);
	ft_printf("%s ", pw->pw_name);
}

void print_time(struct stat *stat) {
	char *time = ctime((const time_t *)&stat->st_mtim);
	ft_printf("%s ", stack_trim(time) + 4);
}

void print_size(off_t size) {
	ft_printf("%d ", size);
}

void print_mode(mode_t mode) {
	char buf[11];
	int k = 0;

	memset(buf, '-', sizeof(buf));
	switch (mode & S_IFMT) {
		case S_IFREG:
			buf[k] = '-';
			break;
		case S_IFDIR:
			buf[k] = 'd';
			break;
		case S_IFLNK:
			buf[k] = 'l';
			break;
		default:
			buf[k] = '?';
	}
	k++;
	for (int i = 0 ; i < 3; i++) {
		if (mode & S_IREAD) {
			buf[k] = 'r';
		}
		k++;
		if (mode & S_IWRITE) {
			buf[k] = 'w';
		}
		k++;
		if (mode & S_IEXEC) {
			buf[k] = 'x';
		}
		k++;
		mode = mode << 3;
	}
	buf[10] = '\0';
	ft_printf("%s ", buf);
}

void print_hardlinks(nlink_t nbrlink) {
	ft_printf("%d ", nbrlink);
}

