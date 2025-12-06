#include "libft.h"

int cmp_normal(const char *str1, const char *str2) {
	if (ft_strcmp(str1, str2) > 0) {
		return (1);
	}
	return (0);
}

int cmp_reverse(const char *str1, const char *str2) {
	if (ft_strcmp(str1, str2) < 0) {
		return (1);
	}
	return (0);
}

char *stack_trim(char *str) {
	while (*str != '\0' && *str == '\n') {
		str++;
	}
	char *tmp = str + (ft_strlen(str) - 1);
	while (str < tmp && *tmp == '\n') {
		tmp--;
	}
	tmp++;
	*tmp = '\0';
	return (str);
}
