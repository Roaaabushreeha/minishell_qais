/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separater.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabu-shr <rabu-shr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:49:13 by rabu-shr          #+#    #+#             */
/*   Updated: 2025/05/20 17:25:54 by rabu-shr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	update_command_counts(t_cmd *cmd_list, int total_cmds)
{
	t_cmd	*cmd_node;

	cmd_node = cmd_list;
	while (cmd_node)
	{
		cmd_node->cmd_count = total_cmds;
		cmd_node = cmd_node->next;
	}
}

void	cleanup_command_list(t_cmd *cmd_list)
{
	t_cmd	*current;
	t_cmd	*next;

	current = cmd_list;
	while (current)
	{
		next = current->next;
		free_commands(current);
		current = next;
	}
}

static t_cmd	*process_command_token(t_token **token, int *cmd_num,
		t_cmd **cmd_node, t_env *env)
{
	t_cmd	*new_cmd;

	new_cmd = command(*cmd_num, token, env);
	if (!new_cmd)
	{
		if (*cmd_node)
			cleanup_command_list(*cmd_node);
		return (NULL);
	}
	if (*cmd_node)
		(*cmd_node)->next = new_cmd;
	*cmd_node = new_cmd;
	(*cmd_num)++;
	return (new_cmd);
}

static t_cmd	*build_command_list(t_token *token, t_env *env, int *total_cmds)
{
	t_cmd	*cmd_list;
	t_cmd	*cmd_node;
	t_cmd	*new_cmd;
	int		cmd_num;

	cmd_node = NULL;
	cmd_list = NULL;
	cmd_num = 1;
	*total_cmds = 0;
	while (token)
	{
		if (token->type != PIPE)
		{
			new_cmd = process_command_token(&token, &cmd_num, &cmd_node, env);
			if (!new_cmd)
				return (NULL);
			if (!cmd_list)
				cmd_list = new_cmd;
			(*total_cmds)++;
		}
		else
			token = token->next;
	}
	return (cmd_list);
}

t_cmd	*separator(t_token *token, t_env *env)
{
	t_cmd	*cmd_list;
	int		total_cmds;

	if (check_quotes_num(token))
	{
		ft_printf("Error: Unmatched quotes\n");
		cleanup_iteration(NULL, NULL, token, NULL);
		return (NULL);
	}
	cmd_list = build_command_list(token, env, &total_cmds);
	if (cmd_list)
		update_command_counts(cmd_list, total_cmds);
	if (!cmd_list)
	{
		cleanup_iteration(NULL, NULL, token, NULL);
		return (NULL);
	}
	return (cmd_list);
}
