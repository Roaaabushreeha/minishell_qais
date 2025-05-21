/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabu-shr <rabu-shr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:31:45 by rabu-shr          #+#    #+#             */
/*   Updated: 2025/05/19 15:25:32 by rabu-shr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	clean_files(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->fd_in != -1)
		{
			close(tmp->fd_in);
			tmp->fd_in = -1;
		}
		if (tmp->fd_out != -1)
		{
			close(tmp->fd_out);
			tmp->fd_out = -1;
		}
		if (tmp->flag_heredoc && tmp->temp)
		{
			unlink(tmp->temp);
			free(tmp->temp);
			tmp->temp = NULL;
		}
		tmp = tmp->next;
	}
	return (1);
}

int	restore_stdout_and_cleanup(int saved_stdout, t_cmd *cmd)
{
	int	status;

	status = 0;
	if (dup2(saved_stdout, STDOUT_FILENO) == -1)
		status = 1;
	close(saved_stdout);
	if (cmd->fd_out != -1)
		close(cmd->fd_out);
	return (status);
}

void	clean_single(t_cmd *cmd, int saved_stdout, int status)
{
	if (cmd->fd_out != -1)
	{
		if (dup2(saved_stdout, STDOUT_FILENO) == -1)
			status = 1;
		close(cmd->fd_out);
		cmd->fd_out = -1;
	}
	if (cmd->fd_in != -1)
	{
		close(cmd->fd_in);
		cmd->fd_in = -1;
	}
	close(saved_stdout);
}
