/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalqam <jalqam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:38:32 by jalqam            #+#    #+#             */
/*   Updated: 2024/09/08 16:28:39 by jalqam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		(*f)(i, &s[i]);
		i++;
	}
}
// int main()
// {
//         void *func = rotone;
//         char str[] = "Hello, World!";
//         printf("%s\n",str);
//         ft_striteri(str, func);
//         printf("%s\n", str); // Outputs: HELLO, WORLD!
//         return (0);
// }
