#include "ft_ls.h"
#include "libft.h"
#include <pwd.h>
#include <grp.h>
#include <time.h>

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
	ft_printf("%d ", mode);
}
