/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalqam <jalqam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:13:05 by jalqam            #+#    #+#             */
/*   Updated: 2025/05/20 19:44:42 by jalqam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_key(char *var)
{
	char	*equal_sign;

	equal_sign = ft_strchr(var, '=');
	if (!equal_sign)
		return (ft_strdup(var));
	return (ft_substr(var, 0, equal_sign - var));
}

int	is_valid_export(char *arg)
{
	int	i;

	i = 0;
	if (!ft_isalpha(arg[i]) && arg[i] != '_')
		return (0);
	i++;
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	handle_invalid_export(char *arg, t_env *env, int *i)
{
	ft_printf("minishell: export: `%s': not a valid identifier\n", arg);
	env->exit_status = 1;
	(*i)++;
}

int	handle_existing_var(t_env *env, char *key, char *arg, int *i)
{
	t_env	*existing;

	existing = find_env_node(key, env);
	if (existing)
	{
		update_env_value(existing, arg);
		free(key);
		(*i)++;
		return (1);
	}
	return (0);
}

int	add_new_var(t_env **env, t_env **last, char *arg, int *i)
{
	t_env	*new_node;

	new_node = create_env_node(arg);
	if (!new_node)
		return (1);
	append_node(env, last, new_node);
	(*i)++;
	return (0);
}
