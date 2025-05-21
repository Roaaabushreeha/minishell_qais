/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabu-shr <rabu-shr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:56:39 by rabu-shr          #+#    #+#             */
/*   Updated: 2025/05/20 16:07:53 by rabu-shr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_env_vars(t_env *env)
{
	int		count;
	t_env	*temp;

	count = 0;
	temp = env;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	return (count);
}

static int	env_array(char **env_arr, t_env *env)
{
	int		count;
	char	*temp2;

	count = 0;
	while (env)
	{
		if (env->value)
		{
			temp2 = ft_strjoin(env->key, "=");
			env_arr[count] = ft_strjoin(temp2, env->value);
			free(temp2);
			if (!env_arr[count])
			{
				ft_free(env_arr);
				return (-1);
			}
			count++;
		}
		env = env->next;
	}
	env_arr[count] = NULL;
	return (count);
}

char	**env_to_array(t_env *env)
{
	char	**env_arr;
	int		count;

	count = count_env_vars(env);
	env_arr = malloc(sizeof(char *) * (count + 1));
	if (!env_arr)
		return (NULL);
	if (env_array(env_arr, env) == -1)
		return (NULL);
	return (env_arr);
}
