/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabu-shr <rabu-shr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:11:31 by rabu-shr          #+#    #+#             */
/*   Updated: 2025/05/14 17:08:41 by rabu-shr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

int	ft_isnumeric(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(char *path, char **s_cmd, int which)
{
	if (which == 0)
		perror("Command not found");
	if (which == 1)
		perror("Execution failed");
	if (which == 2)
		error_handel();
	free(path);
	ft_free(s_cmd);
	exit(1);
}

void	error_handel(void)
{
	perror("Error");
	exit(1);
}

void	ft_free(char **s_cmd)
{
	int	i;

	i = 0;
	while (s_cmd[i])
	{
		free(s_cmd[i]);
		i++;
	}
	free(s_cmd);
}
