/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalqam <jalqam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 13:00:34 by jalqam            #+#    #+#             */
/*   Updated: 2025/01/29 16:44:48 by jalqam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*g_ft_strjoin(char const *s1, char const *s2)
{
	size_t	l1;
	size_t	l2;
	size_t	x;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (l1 + l2 + 1));
	if (!str)
		return (NULL);
	x = 0;
	while (x < l1)
	{
		str[x] = s1[x];
		x++;
	}
	while (x < (l1 + l2))
	{
		str[x] = *s2++;
		x++;
	}
	str[x] = '\0';
	return (str);
}

char	*g_ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

char	*g_ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	x;
	char	*str;

	x = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > (ft_strlen(s) - start))
		len = ft_strlen(s) - start;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (s[start + x] && x < len)
	{
		str[x] = s[start + x];
		x++;
	}
	str[x] = '\0';
	return (str);
}

char	*g_ft_strdup(const char *s)
{
	char	*dest;
	int		x;
	int		len;

	x = 0;
	len = ft_strlen(s);
	if (!s)
		return (NULL);
	dest = (char *)malloc(len * sizeof(char) + 1);
	if (!dest)
		return (NULL);
	while (s[x])
	{
		dest[x] = s[x];
		x++;
	}
	dest[x] = '\0';
	return (dest);
}

size_t	g_ft_strlen(const char *s)
{
	size_t	x;

	x = 0;
	while (*s != '\0')
	{
		x++;
		s++;
	}
	return (x);
}
