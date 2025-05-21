/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expande.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabu-shr <rabu-shr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:59:56 by rabu-shr          #+#    #+#             */
/*   Updated: 2025/05/14 16:40:05 by rabu-shr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*allocate_buffers(char *str, char **var_name)
{
	char	*result;

	result = ft_calloc(ft_strlen(str) * 2 + 1, sizeof(char));
	if (!result)
		return (NULL);
	*var_name = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!*var_name)
	{
		free(result);
		return (NULL);
	}
	return (result);
}

static void	extract_variable_name(char *str, int *i, char *var_name)
{
	int	k;

	k = 0;
	(*i)++;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		var_name[k++] = str[(*i)++];
	var_name[k] = '\0';
}

static void	copy_variable_value(char *result, int *j, char *value)
{
	ft_strlcpy(result + *j, value, ft_strlen(value) + 1);
	*j += ft_strlen(value);
}

char	*expand_variables(char *str, t_env *env, int i)
{
	int		j;
	char	*result;
	char	*value;
	char	*var_name;

	result = allocate_buffers(str, &var_name);
	if (!result)
		return (NULL);
	j = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && str[i + 1] != ' ')
		{
			extract_variable_name(str, &i, var_name);
			value = get_env_value(env, var_name);
			if (value)
				copy_variable_value(result, &j, value);
		}
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	free(var_name);
	return (result);
}
