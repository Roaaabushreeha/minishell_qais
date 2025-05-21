/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalqam <jalqam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 12:15:19 by jalqam            #+#    #+#             */
/*   Updated: 2025/01/28 18:20:56 by jalqam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	char	*str;
	size_t	lenn;
	size_t	i;

	str = (char *)s;
	i = 0;
	lenn = ft_strlen((char *)s);
	if (!str)
		return (NULL);
	if (start > lenn)
		return (ft_strdup(""));
	if (len + start > lenn)
		len = lenn - start;
	ptr = malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	while (str[start + i] && i < len)
	{
		ptr[i] = str[start + i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
