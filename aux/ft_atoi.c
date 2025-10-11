#include "taskmaster.h"
#include "ft_printf.h"

static int	ft_count(const char *str, int i)
{
	int	num;
	int	result;

	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = str[i] - '0';
		result = result * 10 + num;
		i++;
	}
	return (result);
}

int ft_atoi (const char * str){
    int n;
}