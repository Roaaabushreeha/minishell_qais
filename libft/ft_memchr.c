/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalqam <jalqam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:58:49 by jalqam            #+#    #+#             */
/*   Updated: 2024/09/05 14:35:55 by jalqam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*ptr;
	size_t	i;

	ptr = (char *)s;
	i = 0;
	while (i < n)
	{
		if (ptr[i] == (char)c)
			return ((void *)ptr + i);
		i++;
	}
	return (NULL);
}
//  int main ()
//  {
//     char s[]="roaa";
//    printf("%s\n",(char *)ft_memchr(s,'a', 2));
//    //printf("%p",memchr(s,'g', 5));
//  }
