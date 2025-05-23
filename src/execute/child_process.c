/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalqam <jalqam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:59:42 by rabu-shr          #+#    #+#             */
/*   Updated: 2025/05/21 19:14:57 by jalqam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	child_process_heredoc(t_cmd *cmd)
{
	if (cmd->fd_in != -1)
	{
		if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
		{
			perror("heredoc dup2 failed");
			close(cmd->fd_in);
			return (1);
		}
		close(cmd->fd_in);
	}
	if (cmd->temp)
	{
		unlink(cmd->temp);
		free(cmd->temp);
		cmd->temp = NULL;
	}
	return (0);
}

static void	handle_io_redirection(t_cmd *cmd)
{
	if (cmd->fd_out != -1)
	{
		if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
		{
			perror("dup2 error on output");
			exit(1);
		}
		close(cmd->fd_out);
	}
	if (cmd->flag_heredoc)
	{
		if (child_process_heredoc(cmd))
			exit(1);
	}
	else if (cmd->fd_in != -1)
	{
		if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
		{
			perror("dup2 error on input");
			exit(1);
		}
		close(cmd->fd_in);
	}
}

static void	handle_pipe_redirection(t_cmd *cmd, int *fd)
{
	if (!fd)
		return ;
	close(fd[0]);
	if (cmd->next && cmd->fd_out == -1)
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2 error on pipe output");
			exit(1);
		}
	}
	close(fd[1]);
}

static void	execute_command(t_cmd *cmd, t_env *env, char **env_arr,
		t_token *tokens)
{
	char	*cmd_path;
	char	*temp;
	char	*tmp;

	cmd_path = get_path_from_env(cmd->args[0], env);
	if (!cmd_path)
	{
		temp = ft_strdup("minishell: ");
		tmp = ft_strjoin(temp, cmd->args[0]);
		free(temp);
		temp = ft_strjoin(tmp, ": command not found\n");
		if (cmd->args[0][0] != '.')
			env->exit_status = 127;
		free(tmp);
		write(2, temp, ft_strlen(temp));
		free(temp);
		if (env_arr)
			ft_free(env_arr);
		cleanup_and_exit(tokens, cmd, env, env->exit_status);
	}
	execve(cmd_path, cmd->args, env_arr);
	free(cmd_path);
	ft_free(env_arr);
	exit(126);
}

int	child_process(t_cmd *cmd, t_env *env, int *fd, t_token *tokens)
{
	char	**env_arr;
	int		flag;
	int		ret;

	flag = 0;
	ret = 0;
	handle_pipe_redirection(cmd, fd);
	handle_io_redirection(cmd);      
	if (is_builtin_commands(cmd))
	{
		ret = builtin_commands(cmd, env, &flag);
		cleanup_and_exit(tokens, cmd, env, ret);
	}
	env_arr = env_to_array(env);
	execute_command(cmd, env, env_arr, tokens);
	return (0);
}
