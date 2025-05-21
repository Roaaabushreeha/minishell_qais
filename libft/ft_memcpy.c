/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalqam <jalqam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 10:17:49 by jalqam            #+#    #+#             */
/*   Updated: 2024/09/04 12:24:54 by jalqam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*ptr;
	const char	*p;
	size_t		i;

	ptr = (char *)dest;
	p = (char *)src;
	i = 0;
	if (!ptr && !p)
		return (0);
	while (i < n)
	{
		ptr[i] = p[i];
		i++;
	}
	return (dest);
}
