/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_helping.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalqam <jalqam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:59:47 by jalqam            #+#    #+#             */
/*   Updated: 2025/05/21 19:11:32 by jalqam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	setup_pipe(int fd[2], int i, int cmd_count)
{
	if (i < cmd_count - 1)
	{
		if (pipe(fd) == -1)
		{
			perror("Pipe error");
			return (1);
		}
	}
	return (0);
}

void	close_pipe_fds(int fd[2])
{
	if (fd[0] != -1)
	{
		close(fd[0]);
		fd[0] = -1;
	}
	if (fd[1] != -1)
	{
		close(fd[1]);
		fd[1] = -1;
	}
}

void	close_prev_pipe(int *prev_pipe)
{
	if (prev_pipe[0] != -1)
	{
		close(prev_pipe[0]);
		prev_pipe[0] = -1;
	}
	if (prev_pipe[1] != -1)
	{
		close(prev_pipe[1]);
		prev_pipe[1] = -1;
	}
}

int	handle_fork_error(t_cmd *cmd, t_env *env, t_token *tokens,
		t_pipe_fds *pipes)
{
	close_pipe_fds(pipes->fd);
	close_prev_pipe(pipes->prev_pipe);
	free(cmd->args[0]);
	cleanup_and_exit(tokens, cmd, env, 1);
	cmd->error = 1;
	return (1);
}

static void	update_pipes(int fd[2], int prev_pipe[2], int is_last)
{
	if (!is_last)
	{
		close_prev_pipe(prev_pipe);
		prev_pipe[0] = fd[0];
		prev_pipe[1] = fd[1];
	}
	else
	{
		close_pipe_fds(fd);
		close_prev_pipe(prev_pipe);
	}
}

static int	handle_wait_status(t_env *env, int status)
{
	if (WIFEXITED(status))
		env->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		env->exit_status = WTERMSIG(status) + 128;
	else
		env->exit_status = 1;
	return (0);
}

int	execute_commands_pip(t_cmd *cmd, t_env *env, t_token *tokens,
		int prev_pipe[2])
{
	t_cmd		*temp;
	int			error;
	t_pipe_fds	pipes;
	t_fork_data	fork_data;

	fork_data.index = 0;
	temp = cmd;
	while (fork_data.index < cmd->cmd_count && temp)
	{
		fork_data.fd[0] = -1;
		fork_data.fd[1] = -1;
		if (setup_pipe(fork_data.fd, fork_data.index, cmd->cmd_count))
		{
			close_prev_pipe(prev_pipe);
			cleanup_and_exit(tokens, cmd, env, 1);
			return (1);
		}
		fork_data.cmd = temp;
		fork_data.prev_pipe = prev_pipe;
		fork_data.env = env;
		fork_data.tokens = tokens;
		error = init_fork(&fork_data);
		if (error)
		{
			pipes.fd[0] = fork_data.fd[0];
			pipes.fd[1] = fork_data.fd[1];
			pipes.prev_pipe[0] = prev_pipe[0];
			pipes.prev_pipe[1] = prev_pipe[1];
			return (handle_fork_error(cmd, env, tokens, &pipes));
		}
		update_pipes(fork_data.fd, prev_pipe, fork_data.index == cmd->cmd_count - 1);
		temp = temp->next;
		fork_data.index++;
	}
	return (fork_data.index);
}

int	get_cmd_execution(t_cmd *cmd, t_env *env, t_token *tokens)
{
	int	prev_pipe[2];
	int	i;
	int	status;

	prev_pipe[0] = -1;
	prev_pipe[1] = -1;
	if (!cmd || !cmd->args[0])
		return (1);
	i = execute_commands_pip(cmd, env, tokens, prev_pipe);
	if (i <= 0)
		return (1);
	signal_handler(3);
	while (i-- > 0)
		waitpid(-1, &status, 0);
	handle_wait_status(env, status);
	cleanup_heredocs(cmd);
	return (0);
}
