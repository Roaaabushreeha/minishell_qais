/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalqam <jalqam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 13:00:40 by jalqam            #+#    #+#             */
/*   Updated: 2025/01/29 16:44:42 by jalqam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*check(char *ptr)
{
	free(ptr);
	return (NULL);
}

static char	*ft_bufread(int fd, char *last)
{
	char	*ptr;
	char	*la;
	int		re;

	ptr = malloc(BUFFER_SIZE + 1);
	if (!ptr)
		return (check(last));
	re = read(fd, ptr, BUFFER_SIZE);
	while (re > 0)
	{
		ptr[re] = '\0';
		la = ft_strjoin(last, ptr);
		if (!la)
			return (check(ptr));
		free(last);
		last = la;
		if (ft_strchr(ptr, '\n'))
			break ;
		re = read(fd, ptr, BUFFER_SIZE);
	}
	free(ptr);
	if (re < 0 || (re == 0 && (!last || *last == '\0')))
		return (check(last));
	return (last);
}

char	*get_next_line(int fd)
{
	static char	*buf;
	char		*line;
	char		*temp;
	size_t		n;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buf)
		buf = ft_strdup("");
	buf = ft_bufread(fd, buf);
	if (!buf)
		return (check(buf));
	if (!ft_strchr(buf, '\n'))
	{
		line = ft_strdup(buf);
		free(buf);
		buf = NULL;
		return (line);
	}
	n = ft_strchr(buf, '\n') - buf + 1;
	line = ft_substr(buf, 0, n);
	temp = ft_strdup(buf + n);
	free(buf);
	buf = temp;
	return (line);
}
