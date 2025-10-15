#include "taskmaster.h"
#include "ft_printf.h"

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	result;
	int		num;

	i = 0;
	sign = 1;
	result = 0;
	while (isspace((unsigned char)str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = str[i++] - '0';
		if (result > (LONG_MAX - num) / 10)
			return (sign == 1 ? INT_MAX : INT_MIN);
		result = result * 10 + num;
	}
	return ((int)(sign * result));
}