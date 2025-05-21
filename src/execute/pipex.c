/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalqam <jalqam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:14:40 by rabu-shr          #+#    #+#             */
/*   Updated: 2025/05/20 20:22:56 by jalqam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	handle_child_pipes(t_fork_data *data)
{
	if (data->index > 0 && data->cmd->fd_in == -1)
	{
		if (data->prev_pipe[0] != -1)
		{
			dup2(data->prev_pipe[0], STDIN_FILENO);
			close(data->prev_pipe[0]);
		}
		if (data->prev_pipe[1] != -1)
			close(data->prev_pipe[1]);
	}
	if (data->index < data->cmd->cmd_count - 1 && data->cmd->fd_out == -1)
	{
		if (data->fd[1] != -1)
		{
			dup2(data->fd[1], STDOUT_FILENO);
			close(data->fd[1]);
		}
		if (data->fd[0] != -1)
			close(data->fd[0]);
	}
}

int	init_fork(t_fork_data *fork_data)
{
	t_cmd	*temp;
	int		error;

	temp = fork_data->cmd;
	temp->pid = fork();
	signal_handler(1);
	if (temp->pid == 0)
	{
		handle_child_pipes(fork_data);
		error = child_process(fork_data->cmd, fork_data->env,
				NULL, fork_data->tokens);
		if (error)
			cleanup_and_exit(fork_data->tokens, temp, fork_data->env, 126);
	}
	if (fork_data->index > 0)
	{
		close(fork_data->prev_pipe[0]);
		close(fork_data->prev_pipe[1]);
	}
	return (0);
}

// Helper function implementations moved to pipex_helping.c
