/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalqam <jalqam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:02:01 by jalqam            #+#    #+#             */
/*   Updated: 2024/09/05 18:31:00 by jalqam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dsize;
	size_t	ssize;
	size_t	i;

	dsize = ft_strlen((char *)dst);
	ssize = ft_strlen((char *)src);
	i = 0;
	if (size <= dsize)
		return (size + ssize);
	while (src[i] != '\0' && (dsize + i) < (size - 1))
	{
		dst[dsize + i] = src[i];
		i++;
	}
	dst[dsize + i] = '\0';
	return (ssize + dsize);
}
/*
int	main(void)
{
	char	d[20]="talal";
	char	s[]="joud";
	ft_strlcat(d,s, 0);
	printf("%s", d);
}
*/