/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helping.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabu-shr <rabu-shr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:40:33 by rabu-shr          #+#    #+#             */
/*   Updated: 2025/05/19 13:00:51 by rabu-shr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	init_node_values(t_env *node)
{
	node->next = NULL;
	node->pwd = NULL;
	node->exit_status = 0;
	node->reset_flag = 0;
}

static int	set_node_key_value(t_env *node, char *var, char *equal_char)
{
	if (!equal_char)
	{
		node->key = ft_strdup(var);
		node->value = NULL;
	}
	else
	{
		node->key = ft_substr(var, 0, equal_char - var);
		node->value = ft_strdup(equal_char + 1);
	}
	if (!node->key || (equal_char && !node->value))
		return (1);
	return (0);
}

t_env	*create_env_node(char *var)
{
	t_env	*node;
	char	*equal_char;

	node = ft_calloc(1, sizeof(t_env));
	if (!node)
		return (NULL);
	equal_char = ft_strchr(var, '=');
	if (set_node_key_value(node, var, equal_char))
	{
		free_env_node(node);
		return (NULL);
	}
	init_node_values(node);
	return (node);
}
