/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalqam <jalqam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:38:44 by jalqam            #+#    #+#             */
/*   Updated: 2025/05/20 15:49:55 by jalqam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_sorted_env(t_env *sorted)
{
	while (sorted)
	{
		if (sorted->value)
			ft_printf("declare -x %s=\"%s\"\n", sorted->key, sorted->value);
		else
			ft_printf("declare -x %s\n", sorted->key);
		sorted = sorted->next;
	}
}

int	print_export_command(t_env *env)
{
	t_env	*sorted;

	sorted = copy_env_list(env);
	if (!sorted)
		return (1);
	sort_env_list(sorted);
	print_sorted_env(sorted);
	free_env_list(sorted);
	return (0);
}

void	append_node(t_env **env, t_env **last, t_env *new_node)
{
	if (!*env)
		*env = new_node;
	else
		(*last)->next = new_node;
	*last = new_node;
}
