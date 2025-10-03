#include "../incl/taskmaster.h"
#include "../lib/printf/ft_printf.h"

size_t  ft_strlen(char *str)
{
    size_t  len;

    len = 0;
    while (str[len] != '\0')
        len++;
    
    return (len);
}