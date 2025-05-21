/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalqam <jalqam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 17:35:29 by jalqam            #+#    #+#             */
/*   Updated: 2025/02/04 15:26:40 by jalqam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		count;

	i = 0;
	count = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			if (format[i])
				count += ft_check(format[i], args);
		}
		else
		{
			ft_putchar(format[i]);
			count++;
		}
		i++;
	}
	return (count);
}

int	ft_check(char c, va_list args)
{
	if (c == 'd' || c == 'i')
		return (ft_putnum(va_arg(args, int)));
	else if (c == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (c == 'c')
		return (ft_putchar(va_arg(args, int)));
	else if (c == 'u')
		return (ft_putun(va_arg(args, unsigned int)));
	else if (c == '%')
		return (ft_putchar('%'));
	else if (c == 'x')
		return (ft_puthex(va_arg(args, unsigned int)));
	else if (c == 'X')
		return (ft_puthexx(va_arg(args, unsigned int)));
	else if (c == 'p')
		return (ft_pointer(va_arg(args, unsigned long), "0123456789abcdef"));
	else
		return (0);
}
