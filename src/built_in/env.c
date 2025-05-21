/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalqam <jalqam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:27:24 by jalqam            #+#    #+#             */
/*   Updated: 2025/05/20 19:44:41 by jalqam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*init_envp(char **env_list)
{
	t_env	*env;
	t_env	*last;
	t_env	*temp;
	int		i;

	i = 0;
	env = NULL;
	last = NULL;
	while (env_list[i])
	{
		temp = create_env_node(env_list[i]);
		if (!temp)
		{
			free_env_node(env);
			free_env_list(env);
			free(env->pwd);
			return (NULL);
		}
		append_node(&env, &last, temp);
		i++;
	}
	return (env);
}

t_env	*find_env_node(char *key, t_env *env)
{
	if (!env || !key)
		return (NULL);
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	update_env_value(t_env *node, char *var)
{
	char	*equal_sign;
	char	*new_value;

	equal_sign = ft_strchr(var, '=');
	if (!equal_sign)
		return ;
	new_value = ft_strdup(equal_sign + 1);
	free(node->value);
	node->value = new_value;
}

int	handle_pwd(void)
{
	char	*word;

	word = getcwd(NULL, 0);
	if (word)
	{
		printf("%s\n", word);
		free(word);
		return (0);
	}
	return (1);
}
