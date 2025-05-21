/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalqam <jalqam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:21:39 by jalqam            #+#    #+#             */
/*   Updated: 2024/09/04 12:33:14 by jalqam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		len;
	char	*str;

	str = (char *)s;
	len = ft_strlen(str);
	while (len >= 0)
	{
		if (str[len] == (char)c)
			return (str + len);
		len--;
	}
	if (c == '\0')
		return (str + len);
	return (NULL);
}

// int main()
// {
// 	char	c[]="teste";
// 	char *cc=ft_strrchr(c,'f');
// 	printf("%p\n",cc);
//         char *aa=strrchr(c,'f');
//         printf("%p",aa);
// }
