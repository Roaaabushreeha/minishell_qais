/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalqam <jalqam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 17:03:47 by jalqam            #+#    #+#             */
/*   Updated: 2024/12/21 15:05:36 by jalqam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	char	*c;
	int		i;
	int		sign;
	int		res;

	if (!nptr)
		return (0);
	c = (char *)nptr;
	i = 0;
	sign = 1;
	res = 0;
	while ((c[i] >= 9 && c[i] <= 13) || c[i] == 32)
		i++;
	if (c[i] == '-' || c[i] == '+')
	{
		if (c[i] == '-')
			sign = -sign;
		i++;
	}
	while (c[i] >= '0' && c[i] <= '9' && c[i] != '\0')
	{
		res = (res * 10) + c[i] - '0';
		i++;
	}
	return (sign * res);
}
// int main()
// {
//    char c[]="  -6666";
//    int a = ft_atoi(c);
//    printf("%d\n",a);
//    int b = atoi(c);
//    printf("%d\n",b);
// }
