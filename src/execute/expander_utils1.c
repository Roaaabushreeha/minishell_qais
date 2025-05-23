/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falhaimo <falhaimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:17:48 by falhaimo          #+#    #+#             */
/*   Updated: 2025/05/21 17:18:10 by falhaimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_dollar_status(t_expander *s, t_env *env)
{
	char	*status;

	status = get_exit_status(env);
	if (status)
	{
		s->temp = s->result;
		s->result = ft_strjoin(s->result, status);
		free(s->temp);
		free(status);
	}
	s->i += 2;
}

int	handle_dollar_param_expansion(t_expander *s)
{
	s->special = handle_dollar_param(s->str + s->i, &s->i);
	if (s->special)
	{
		s->temp = s->result;
		s->result = ft_strjoin(s->result, s->special);
		free(s->temp);
		free(s->special);
		return (1);
	}
	return (0);
}

int	extract_env_var_name(t_expander *s)
{
	s->i++;
	s->start = s->i;
	if (s->str[s->i] == '$')
		s->i++;
	else
		while (s->str[s->i] && (ft_isalnum(s->str[s->i])
				|| s->str[s->i] == '_'))
			s->i++;
	s->var_name = ft_substr(s->str, s->start, s->i - s->start);
	if (!s->var_name)
		return (0);
	return (1);
}

int	append_env_var_value(t_expander *s, t_env *env)
{
	s->var_value = get_env_value(env, s->var_name);
	s->temp = s->result;
	if (s->var_value)
	{
		if (!s->in_dquotes)
		{
			s->cleaned = epur_string(s->var_value);
			if (s->cleaned)
			{
				s->result = ft_strjoin(s->result, s->cleaned);
				free(s->cleaned);
			}
		}
		else
			s->result = ft_strjoin(s->result, s->var_value);
	}
	else
		s->result = ft_strjoin(s->result, "");
	free(s->temp);
	if (!s->result)
		return (0);
	return (1);
}

int	handle_env_var_expansion(t_expander *s, t_env *env)
{
	if (!extract_env_var_name(s))
	{
		free(s->result);
		return (0);
	}
	if (!append_env_var_value(s, env))
	{
		free(s->var_name);
		return (0);
	}
	free(s->var_name);
	return (1);
}
