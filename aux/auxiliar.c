#include "taskmaster.h"
#include "ft_printf.h"

char* ft_substr(const char *src, int start, int length) {
    int src_len = strlen(src);

    if (start < 0 || start >= src_len || length <= 0)
        return NULL;

    if (start + length > src_len)
        length = src_len - start;

    char *sub = malloc(length + 1);
    if (sub == NULL)
        return NULL;

    strncpy(sub, src + start, length);
    sub[length] = '\0';

    return sub;
}

int	ft_strcmp(const char *s1, const char *s2) {
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

bool ft_atob(const char *str) {
    return (str && ft_strcmp(str, "true") == 0) ? true : false;
}
