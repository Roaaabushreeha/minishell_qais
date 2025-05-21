/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoce_processer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalqam <jalqam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:39:42 by rabu-shr          #+#    #+#             */
/*   Updated: 2025/05/19 18:19:26 by jalqam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	write_heredoc_line(int fd, char *buffer, int quoted, t_env *env)
{
	if (!quoted)
		write_heredoc_expanded(fd, buffer, NULL, env);
	else
	{
		write(fd, buffer, ft_strlen(buffer));
		write(fd, "\n", 1);
	}
	free(buffer);
}

int	check_heredoc_exit(char *buffer, t_env *env)
{
	if (!buffer || g_signals_status == 130)
	{
		if (buffer)
			free(buffer);
		env->exit_status = 130;
		env->reset_flag = 1;
		dup2(STDOUT_FILENO, STDIN_FILENO);
		return (1);
	}
	return (0);
}
