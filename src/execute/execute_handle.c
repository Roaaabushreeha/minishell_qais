/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_handle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabu-shr <rabu-shr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:41:53 by rabu-shr          #+#    #+#             */
/*   Updated: 2025/05/20 16:08:45 by rabu-shr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_pipe_case(t_cmd *cmd, t_env *env, t_token *token)
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

int	handle_builtin_case(t_cmd *cmd, t_env *env, t_token *token)
{
	int	status;
	int	flag;

	flag = 0;
	if (execute_command_temp(cmd, env, token))
		return (0);
	status = handle_single_command(cmd, env, token, &flag);
	return (status);
}

int	handle_pipe_execution(t_cmd *cmd, t_env *env, t_token *token)
{
	int	pipe_count;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	pipe_count = num_pip(token);
	if (pipe_count > 0)
		return (handle_pipe_case(cmd, env, token));
	if (is_builtin_commands(cmd))
		return (handle_builtin_case(cmd, env, token));
	return (handle_pipe_case(cmd, env, token));
}
