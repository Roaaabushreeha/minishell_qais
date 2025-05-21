/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalqam <jalqam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 16:22:14 by jalqam            #+#    #+#             */
/*   Updated: 2024/12/16 17:36:49 by jalqam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s != '\0')
		{
			count++;
			while (*s && *s != c)
				s++;
		}
	}
	return (count);
}

static char	**free_split(char **split)
{
	char	**temp;

	temp = split;
	if (split)
	{
		while (*temp)
		{
			free(*temp);
			temp++;
		}
		free(split);
	}
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		i;
	int		j;
	int		a;

	i = 0;
	a = 0;
	j = 0;
	str = ft_calloc((ft_count_words((char *)s, c) + 1), sizeof(char *));
	if (!str)
		return (NULL);
	while (a < ft_count_words((char *)s, c))
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		j = i;
		while (s[i] != c && s[i] != '\0')
			i++;
		str[a] = ft_substr(s, j, i - j);
		if (!str[a])
			return (free_split(str));
		a++;
	}
	return (str);
}

// int main ()
// {
// 	char *str = "Hello, World!";
//         char **split;

//         split = ft_split(str, ',');
//         for (int i = 0; split[i]; i++)
//                 printf("%s\n", split[i]);
//         free_split(split);
//         return (0);
// }