/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalqam <jalqam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 18:36:17 by jalqam            #+#    #+#             */
/*   Updated: 2024/12/16 17:21:16 by jalqam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	lenst(long n)
{
	size_t	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		len++;
	while ((n != 0))
	{
		n /= 10;
		len++;
	}
	return (len);
}

static char	*init(int *len, int n)
{
	*len = lenst(n);
	return (ft_calloc((*len + 1), sizeof(char)));
}

char	*ft_itoa(int n)
{
	int		sign;
	char	*final;
	int		i;

	sign = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	final = init(&i, n);
	if (!final)
		return (NULL);
	if (n < 0)
	{
		sign = -1;
		n *= -1;
	}
	while (i > 0)
	{
		final[i - 1] = (n % 10) + '0';
		i--;
		n /= 10;
	}
	if (sign == -1)
		final[i] = '-';
	return (final);
}
// int main()
// {
//         int n = 0;
//         char *str = ft_itoa(n);
//         printf("%s",str);
// }