#include "taskmaster.h"
#include "ft_printf.h"

int ft_atoi(char *str)
{
    long long num;
    int i;

    if (!str || !*str)
        return (-1);
    
    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] < '0' || str[i] > '9')
            return (-1);
        i++;
    }

    num = 0;
    i = 0;
    while (str[i] != '\0')
    {
        num = num * 10 + (str[i] - '0');
        if (num > INT_MAX)
            return (-1);
        i++; 
    }
    return ((int)num);
}