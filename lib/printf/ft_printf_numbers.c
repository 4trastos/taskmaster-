/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_numbers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:03:52 by davgalle          #+#    #+#             */
/*   Updated: 2023/11/03 22:02:08 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr(int nb, int *count)
{
	if (*count == -1)
		return ;
	if (nb == -2147483648)
	{
		if (write(1, "-2147483648", 11) == -1)
			*count = -1;
		else
			(*count) += 11;
		return ;
	}
	if (nb < 0)
	{
		ft_putchar('-', count);
		ft_putnbr(nb * -1, count);
	}
	else
	{
		if (nb > 9)
			ft_putnbr(nb / 10, count);
		if (*count != -1)
			ft_putchar(nb % 10 + '0', count);
	}
}

void	ft_putunsign(unsigned int nb, int *count)
{
	if (*count == -1)
		return ;
	if (nb >= 10)
	{
		ft_putunsign(nb / 10, count);
		ft_putunsign(nb % 10, count);
	}
	else
		ft_putchar(nb + 48, count);
}

void	ft_hexa(unsigned long long nb, char *base, int *count)
{
	if (*count == -1)
		return ;
	if (nb >= 16)
	{
		ft_hexa(nb / 16, base, count);
		ft_hexa(nb % 16, base, count);
	}
	else
		ft_putchar(base[nb], count);
}
