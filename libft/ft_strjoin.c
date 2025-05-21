/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalqam <jalqam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 14:40:10 by jalqam            #+#    #+#             */
/*   Updated: 2024/08/31 16:17:33 by jalqam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	size_t	l1;
	size_t	l2;
	int		i;
	int		point;

	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	i = 0;
	point = 0;
	p = malloc(sizeof(char) * (l1 + l2 + 1));
	if (p == NULL)
		return (NULL);
	while (s1[i] != '\0')
		p[point++] = s1[i++];
	i = 0;
	while (s2[i] != '\0')
		p[point++] = s2[i++];
	p[point] = '\0';
	return (p);
}
// int main()
// {
//         char *s1 = "Hello";
//         char *s2 = "World";
//         char *result = ft_strjoin(s1, s2);
//         printf("Result: %s\n", result);
//         free(result);
//         return (0);

// }