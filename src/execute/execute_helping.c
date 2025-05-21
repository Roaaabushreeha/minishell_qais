/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_helping.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabu-shr <rabu-shr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 13:37:56 by rabu-shr          #+#    #+#             */
/*   Updated: 2025/05/20 18:29:07 by rabu-shr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_print(t_env *env)
{
	if (!env)
		return ;
	while (env)
	{
		if (env->value)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}

void	exit_command(t_cmd *cmds, t_env *env, t_token *token)
{
	int	exit_code;

	exit_code = 0;
	if (cmds->args[1])
	{
		exit_code = ft_atoi(cmds->args[1]);
		if (!ft_isnumeric(cmds->args[1]))
		{
			printf("exit\n");
			printf("minishell: exit: %s: numeric argument required\n",
					cmds->args[1]);
			if (env->pwd)
				free(env->pwd);
			free_tokens(token);
			free_commands(cmds);
			free_env_list(env);
			exit(1);
		}
		if (env->pwd)
			free(env->pwd);
		free_tokens(token);
		free_commands(cmds);
		free_env_list(env);
		exit(exit_code);
	}
	g_signals_status = env->exit_status;
	printf("exit\n");
	free(env->pwd);
	free_tokens(token);
	free_commands(cmds);
	free_env_list(env);
	exit(g_signals_status);
}

int	num_pip(t_token *token)
{
	int		pipe_count;
	t_token	*temp;

	pipe_count = 0;
	temp = token;
	if (!temp)
		return (0);
	while (temp)
	{
		if (temp->value && ft_strcmp(temp->value, "|") == 0)
		{
			pipe_count++;
		}
		temp = temp->next;
	}
	return (pipe_count);
}

int	is_builtin_commands(t_cmd *cmd)
{
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		return (1);
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		return (1);
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		return (1);
	return (0);
}

int	handle_single_command(t_cmd *cmd, t_env *env, t_token *token, int *flag)
{
	int	status;
	int	saved_stdout;

	(void)token;
	status = 0;
	if (!cmd || !cmd->args[0])
		return (0);
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdout == -1)
		return (1);
	if (cmd->fd_out != -1)
	{
		if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
		{
			close(saved_stdout);
			return (1);
		}
	}
	status = builtin_commands(cmd, env, flag);
	clean_single(cmd, saved_stdout, status);
	return (status);
}
