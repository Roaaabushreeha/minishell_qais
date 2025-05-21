/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalqam <jalqam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 11:19:47 by jalqam            #+#    #+#             */
/*   Updated: 2025/02/04 15:26:33 by jalqam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		s = "(null)";
	while (s[i])
		write(1, &s[i++], 1);
	return (i);
}

int	ft_putnum(int n)
{
	long	nb;
	char	c;
	int		count;

	count = 0;
	nb = n;
	if (nb < 0)
	{
		write(1, "-", 1);
		nb = -nb;
		count++;
	}
	if (nb >= 10)
		count += ft_putnum(nb / 10);
	c = nb % 10 + '0';
	write(1, &c, 1);
	count++;
	return (count);
}

int	ft_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putun(unsigned int n)
{
	long	nb;
	char	c;
	int		count;

	count = 0;
	nb = n;
	if (nb >= 10)
		count += ft_putnum(nb / 10);
	c = nb % 10 + '0';
	write(1, &c, 1);
	count++;
	return (count);
}

int	ft_puthex(unsigned int n)
{
	long	nb;
	char	c;
	int		count;
	char	*hex;

	count = 0;
	hex = "0123456789abcdef";
	nb = n;
	if (nb >= 16)
		count += ft_puthex(nb / 16);
	c = hex[nb % 16];
	write(1, &c, 1);
	count++;
	return (count);
}
