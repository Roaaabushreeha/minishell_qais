/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalqam <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:41:55 by jalqam            #+#    #+#             */
/*   Updated: 2024/08/26 18:46:41 by jalqam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include <stdio.h>
#include <string.h>

void	*ft_memset(void *s, int c, size_t n)
{
	char	*ptr;

	ptr = s;
	while (n)
	{
		*ptr = c;
		n--;
		ptr++;
	}
	return (s);
}
/*
int	main(void)
{
	char	c[]="joud";
	printf("%s",(char *)ft_memset(c, 'a', 3));
	printf("\n");
	printf("%s",(char *)memset(c, 'a', 3));
}
*/
