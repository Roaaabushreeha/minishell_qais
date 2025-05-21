/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabu-shr <rabu-shr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:35:05 by rabu-shr          #+#    #+#             */
/*   Updated: 2025/05/14 17:15:32 by rabu-shr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_env_node(t_env *node)
{
	if (!node)
		return ;
	if (node->key)
		free(node->key);
	if (node->value)
		free(node->value);
	free(node);
}

void	free_env_list(t_env *env)
{
	t_env	*temp;
	t_env	*next;

	temp = env;
	while (temp)
	{
		next = temp->next;
		free_env_node(temp);
		temp = next;
	}
}

void	free_cmd(t_cmd *cmd)
{
	int	i;

	if (cmd->args)
	{
		i = -1;
		while (cmd->args[++i])
		{
			free(cmd->args[i]);
			cmd->args[i] = NULL;
		}
		free(cmd->args);
		cmd->args = NULL;
	}
	if (cmd->type)
	{
		free(cmd->type);
		cmd->type = NULL;
	}
	if (cmd->temp)
	{
		free(cmd->temp);
		cmd->temp = NULL;
	}
	free(cmd);
}

void	free_cmd_list(t_cmd *cmd_list)
{
	t_cmd	*tmp;

	while (cmd_list)
	{
		tmp = cmd_list;
		cmd_list = cmd_list->next;
		free_cmd(tmp);
	}
}
