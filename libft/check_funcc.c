/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_funcc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalqam <jalqam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:42:38 by jalqam            #+#    #+#             */
/*   Updated: 2025/02/04 15:26:37 by jalqam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_puthexx(unsigned int n)
{
	long	nb;
	char	c;
	int		count;
	char	*hex;

	count = 0;
	hex = "0123456789ABCDEF";
	nb = n;
	if (nb >= 16)
		count += ft_puthexx(nb / 16);
	c = hex[nb % 16];
	write(1, &c, 1);
	count++;
	return (count);
}

int	ft_pointer(unsigned long n, char *h)
{
	char	c[17];
	int		count;
	int		i;

	i = 0;
	count = 0;
	if (n == 0)
		return (ft_putstr("(nil)"));
	count += ft_putstr("0x");
	while (n > 0)
	{
		c[i] = h[n % 16];
		n /= 16;
		i++;
	}
	c[i] = '\0';
	while (--i >= 0)
	{
		write(1, &c[i], 1);
		count++;
	}
	return (count);
}
