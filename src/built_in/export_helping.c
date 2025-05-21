/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helping.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalqam <jalqam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:36:02 by jalqam            #+#    #+#             */
/*   Updated: 2025/05/20 15:49:25 by jalqam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	export_command(t_cmd *cmd, t_env **env)
{
	int		i;
	t_env	*last;
	char	*key;

	i = 1;
	if (!cmd->args[i])
		return (print_export_command(*env));
	last = *env;
	while (last && last->next)
		last = last->next;
	while (cmd->args[i])
	{
		if (!is_valid_export(cmd->args[i]))
		{
			handle_invalid_export(cmd->args[i], *env, &i);
			continue ;
		}
		key = get_key(cmd->args[i]);
		if (handle_existing_var(*env, key, cmd->args[i], &i))
			continue ;
		free(key);
		if (add_new_var(env, &last, cmd->args[i], &i))
			return (1);
	}
	return (0);
}

void	swap_nodes(t_env *a, t_env *b)
{
	char	*temp_key;
	char	*temp_value;

	temp_key = a->key;
	temp_value = a->value;
	a->key = b->key;
	a->value = b->value;
	b->key = temp_key;
	b->value = temp_value;
}

t_env	*create_env_copy_node(t_env *env)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_strdup(env->key);
	if (env->value)
		new->value = ft_strdup(env->value);
	else
		new->value = NULL;
	new->next = NULL;
	if (!new->key || (env->value && !new->value))
	{
		free_env_node(new);
		return (NULL);
	}
	return (new);
}

t_env	*copy_env_list(t_env *env)
{
	t_env	*copy;
	t_env	*new;
	t_env	*last;

	copy = NULL;
	last = NULL;
	while (env)
	{
		new = create_env_copy_node(env);
		if (!new)
		{
			free_env_list(copy);
			return (NULL);
		}
		if (!copy)
			copy = new;
		else
			last->next = new;
		last = new;
		env = env->next;
	}
	return (copy);
}

void	sort_env_list(t_env *sorted)
{
	t_env	*j;
	int		swapped;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		j = sorted;
		while (j->next)
		{
			if (ft_strcmp(j->key, j->next->key) > 0)
			{
				swap_nodes(j, j->next);
				swapped = 1;
			}
			j = j->next;
		}
	}
}
