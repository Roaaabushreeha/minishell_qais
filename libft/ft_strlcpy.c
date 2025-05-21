/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalqam <jalqam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:54:37 by jalqam            #+#    #+#             */
/*   Updated: 2024/09/05 18:45:02 by jalqam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	char	*s;

	i = 0;
	s = (char *)src;
	if (size == 0)
		return (ft_strlen((char *)src));
	while (s[i] != '\0' && i < (size - 1))
	{
		dst[i] = s[i];
		i++;
	}
	dst[i] = '\0';
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}
// int main()
// {
// 	char s[]="joud";
// 	char d[10];
// 	printf("%ld",ft_strlcpy(d,s,4));
// 	//printf("%ld",strlcpy(d,s,4));
// }
