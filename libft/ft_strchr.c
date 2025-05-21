/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalqam <jalqam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 13:57:58 by jalqam            #+#    #+#             */
/*   Updated: 2024/09/05 18:09:50 by jalqam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	uc;
	char			*ss;

	ss = (char *)s;
	uc = (unsigned char)c;
	while (*ss != '\0')
	{
		if (*ss == uc)
			return (ss);
		ss++;
	}
	if (*ss == '\0' && uc != '\0')
		return (NULL);
	return (ss);
}
// int main()
// {
// 	char c[] ="joud";
// 	char *cc=ft_strchr(c, 354);
// 	printf("%s",cc );
// }
