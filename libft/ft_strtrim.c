/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalqam <jalqam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 16:24:19 by jalqam            #+#    #+#             */
/*   Updated: 2024/09/01 11:57:23 by jalqam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*p;
	size_t	len;
	size_t	start;
	size_t	end;

	len = ft_strlen(s1);
	start = 0;
	end = len - 1;
	if (!s1 || !set)
		return (NULL);
	while (start <= end && ft_strchr(set, s1[start]))
		start++;
	while (start <= end && ft_strchr(set, s1[end]))
		end--;
	if (start > end)
	{
		p = (char *)malloc(1);
		if (!p)
			return (NULL);
		p[0] = '\0';
		return (p);
	}
	p = ft_substr(s1, start, end - start + 1);
	return (p);
}
