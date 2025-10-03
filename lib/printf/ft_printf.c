/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 19:15:28 by davgalle          #+#    #+#             */
/*   Updated: 2023/11/03 22:01:27 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_whattype(char c, va_list args, int *nb)
{
	if (c == 'c')
		ft_putchar(va_arg(args, int), nb);
	else if (c == 's')
		ft_putstr(va_arg(args, char *), nb);
	else if (c == 'p')
	{
		ft_putstr("0x", nb);
		if (*nb != -1)
			ft_hexa(va_arg(args, unsigned long long), "0123456789abcdef", nb);
	}
	else if (c == 'd')
		ft_putnbr(va_arg(args, int), nb);
	else if (c == 'i')
		ft_putnbr(va_arg(args, int), nb);
	else if (c == 'u')
		ft_putunsign(va_arg(args, unsigned int), nb);
	else if (c == 'x')
		ft_hexa(va_arg(args, unsigned int), "0123456789abcdef", nb);
	else if (c == 'X')
		ft_hexa(va_arg(args, unsigned int), "0123456789ABCDEF", nb);
	else if (c == '%')
		ft_putchar('%', nb);
}

int	ft_printf(char const *format, ...)
{
	va_list	args;
	int		count;
	int		i;

	i = 0;
	count = 0;
	va_start(args, format);
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			ft_whattype(format[i + 1], args, &count);
			i++;
		}
		else
			ft_putchar(format[i], &count);
		i++;
		if (count < 0)
			return (-1);
	}
	va_end(args);
	return (count);
}
