/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabu-shr <rabu-shr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:42:26 by rabu-shr          #+#    #+#             */
/*   Updated: 2025/05/20 17:21:52 by rabu-shr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_cmd	*init_command_struct(void)
{
	t_cmd	*new_cmd;

	new_cmd = init_cmd();
	if (!new_cmd)
		return (NULL);
	return (new_cmd);
}

static int	process_token(t_token **token, t_cmd *new_cmd, int *count_cmd,
		t_env *env)
{
	if ((*token)->value && is_redirect((*token)->value))
	{
		if (handle_redirection(token, new_cmd, env))
		{
			free_cmd(new_cmd);
			return (1);
		}
		return (2);
	}
	if ((*token)->value && add_command_arg(new_cmd, *token, count_cmd, env))
	{
		free_cmd(new_cmd);
		return (1);
	}
	*token = (*token)->next;
	return (0);
}

static void	finalize_command(t_cmd *new_cmd, t_token **token, int count_cmd,
		int cmd_num)
{
	new_cmd->args[count_cmd] = NULL;
	new_cmd->command_num = cmd_num;
	if (*token && ft_strcmp((*token)->value, "|") == 0)
		*token = (*token)->next;
}

t_cmd	*command(int cmd_num, t_token **token, t_env *env)
{
	t_cmd	*new_cmd;
	int		count_cmd;
	int		process_result;

	count_cmd = 0;
	new_cmd = init_command_struct();
	if (!new_cmd)
		return (NULL);
	while (*token && ft_strcmp((*token)->value, "|") != 0)
	{
		process_result = process_token(token, new_cmd, &count_cmd, env);
		if (process_result == 1)
			return (NULL);
		if (process_result == 2)
			continue ;
	}
	finalize_command(new_cmd, token, count_cmd, cmd_num);
	return (new_cmd);
}

int	add_command_arg(t_cmd *new_cmd, t_token *token, int *count_cmd, t_env *env)
{
	char	*processed_value;

	processed_value = process_command_arg(token, (*count_cmd == 0), env);
	if (!processed_value)
	{
		cleanup_iteration(NULL, NULL, token, new_cmd);
		return (1);
	}
	new_cmd->args[(*count_cmd)++] = processed_value;
	return (0);
}
