/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalqam <jalqam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 12:03:11 by jalqam            #+#    #+#             */
/*   Updated: 2024/12/16 17:19:15 by jalqam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const char	*sr;
	char		*dst;
	size_t		i;

	sr = src;
	dst = dest;
	i = n;
	if (sr == dst || n == 0)
		return (dest);
	if (dst < sr)
	{
		ft_memcpy(dst, sr, n);
	}
	else
	{
		while (i > 0)
		{
			dst[i - 1] = sr[i - 1];
			i--;
		}
	}
	return (dest);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	str[100];

	str[100] = "Learningisfun";
	char *first, *second;
	first = str;
	second = str;
	printf("Original string :%s\n ", str);
	// when overlap happens then it just ignore it
	memcpy(first + 8, first, 10);
	printf("memcpy overlap : %s\n ", str);
	// when overlap it start from first position
	ft_memmove(second + 8, first, 10);
	printf("memmove overlap : %s\n ", str);
	return (0);
}
*/
