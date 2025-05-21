/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabu-shr <rabu-shr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:43:07 by rabu-shr          #+#    #+#             */
/*   Updated: 2025/05/20 19:19:16 by rabu-shr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_command_temp(t_cmd *cmd, t_env *env, t_token *token)
{
	if (ft_strcmp(cmd->args[0], "echo") == 0)
	{
		echo_command(cmd, env);
		return (1);
	}
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
	{
		exit_command(cmd, env, token);
		return (1);
	}
	return (0);
}

int	handle_builtin_execution(t_cmd *cmd, t_env *env, t_token *token)
{
	int	status;
	int	flag;

	flag = 0;
	if (execute_command_temp(cmd, env, token))
		return (0);
	status = handle_single_command(cmd, env, token, &flag);
	return (status);
}

int	handle_regular_execution(t_cmd *cmd, t_env *env, t_token *token)
{
	int	status;

	status = get_cmd_execution(cmd, env, token);
	if (status == 1)
	{
		cleanup_resources(env, token, cmd);
		return (1);
	}
	return (status);
}

int	execute_commands(t_cmd *cmd, t_env *env, t_token *token)
{
	int	pipe_count;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	pipe_count = num_pip(token);
	if (pipe_count > 0)
		return (handle_pipe_execution(cmd, env, token));
	if (is_builtin_commands(cmd))
		return (handle_builtin_execution(cmd, env, token));
	return (handle_regular_execution(cmd, env, token));
}
