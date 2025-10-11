#include "taskmaster.h"
#include "ft_printf.h"

size_t  ft_strlen(char *str)
{
    size_t  len;

    len = 0;
    while (str[len] != '\0')
        len++;
    
    return (len);
}

char* substr(const char *src, int start, int length) {
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