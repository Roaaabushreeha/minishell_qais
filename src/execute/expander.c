/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falhaimo <falhaimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:43:00 by rabu-shr          #+#    #+#             */
/*   Updated: 2025/05/21 17:10:35 by falhaimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	update_quote_state(char c, int *in_dq, int *in_sq)
{
	if (c == '"' && !(*in_sq))
	{
		*in_dq = !(*in_dq);
		return (1);
	}
	if (c == '\'' && !(*in_dq))
	{
		*in_sq = !(*in_sq);
		return (1);
	}
	return (0);
}

char	*append_char_to_result(char *result, char c)
{
	char	*old_result = result;
	char	new_char[2];

	new_char[0] = c;
	new_char[1] = '\0';
	result = ft_strjoin(result, new_char);
	free(old_result);
	return (result);
}

char	*handle_mixed_quotes(t_token *token)
{
	int		i;
	int		in_dq;
	int		in_sq;
	char	*result;

	if (!token || !token->value)
		return (NULL);
	result = ft_strdup("");
	i = 0;
	in_dq = 0;
	in_sq = 0;
	while (token->value[i])
	{
		if (update_quote_state(token->value[i], &in_dq, &in_sq))
			i++;
		else
			result = append_char_to_result(result, token->value[i++]);
	}
	return (result);
}

// char	*handle_twoquotes(t_token *token)
// {
// 	char	*str;
// 	char	*result;
// 	int		i;
// 	int		j;

// 	str = ft_strdup(token->value);
// 	result = malloc(ft_strlen(str) + 1);
// 	if (!result)
// 		return (NULL);
// 	i = 0;
// 	j = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '"' && (i == 0 || str[i - 1] != '\\'))
// 		{
// 			i++;
// 			while (str[i] && str[i] != '"')
// 				result[j++] = str[i++];
// 			if (str[i])
// 				i++;
// 		}
// 		else
// 			result[j++] = str[i++];
// 	}
// 	result[j] = '\0';
// 	free(str);
// 	return (result);
// }
static void	copy_inside_quotes(const char *str, char *result, int *i, int *j)
{
	(*i)++;
	while (str[*i] && str[*i] != '"')
		result[(*j)++] = str[(*i)++];
	if (str[*i])
		(*i)++; // Skip the closing quote
}

static void	copy_outside_quotes(const char *str, char *result, int *i, int *j)
{
	result[(*j)++] = str[(*i)++];
}

char	*handle_twoquotes(t_token *token)
{
	char	*str;
	char	*result;
	int		i;
	int		j;

	str = ft_strdup(token->value);
	if (!str)
		return (NULL);
	result = malloc(ft_strlen(str) + 1);
	if (!result)
	{
		free(str);
		return (NULL);
	}
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '"' && (i == 0 || str[i - 1] != '\\'))
			copy_inside_quotes(str, result, &i, &j);
		else
			copy_outside_quotes(str, result, &i, &j);
	}
	result[j] = '\0';
	free(str);
	return (result);
}

char	*handle_onequote_expander(t_token *token)
{
	char	*result;
	char	*value;
	int		i;
	int		inside_quotes;

	if (!token || !token->value)
		return (NULL);
	result = ft_strdup("");
	if (!result)
		return (NULL);
	value = token->value;
	inside_quotes = 0;
	i = 0;
	while (value[i])
	{
		if (value[i] == '\'')
		{
			inside_quotes = !inside_quotes;
			i++;
			continue ;
		}
		append_char_to_result(result, value[i]);
		i++;
	}
	return (result);
}
static void	skip_leading_spaces(char *str, int *i)
{
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
		(*i)++;
}

static void	append_cleaned_word(char *str, char *result, int *i, int *j)
{
	int	space = 0;

	while (str[*i])
	{
		if (str[*i] == ' ' || str[*i] == '\t')
			space = 1;
		else
		{
			if (space && *j > 0)
			{
				result[(*j)++] = ' ';
				space = 0;
			}
			result[(*j)++] = str[*i];
		}
		(*i)++;
	}
}

char	*epur_string(char *str)
{
	char	*result;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	result = malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	skip_leading_spaces(str, &i);
	append_cleaned_word(str, result, &i, &j);
	result[j] = '\0';
	return (result);
}

typedef struct s_expander
{
	char    *result;
	char    *str;
	int     i;
	int     start;
	int     in_squotes;
	int     in_dquotes;
	char    *var_name;
	char    *var_value;
	char    *cleaned;
	char    *temp;
	char    *special;
}   t_expander;
static void	handle_dollar_status(t_expander *s, t_env *env)
{
	char *status = get_exit_status(env);
	if (status)
	{
		s->temp = s->result;
		s->result = ft_strjoin(s->result, status);
		free(s->temp);
		free(status);
	}
	s->i += 2;
}

static int	handle_dollar_param_expansion(t_expander *s)
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

static int	extract_env_var_name(t_expander *s)
{
	s->i++;
	s->start = s->i;
	if (s->str[s->i] == '$')
		s->i++;
	else
		while (s->str[s->i] && (ft_isalnum(s->str[s->i]) || s->str[s->i] == '_'))
			s->i++;
	s->var_name = ft_substr(s->str, s->start, s->i - s->start);
	if (!s->var_name)
		return (0);
	return (1);
}

static int	append_env_var_value(t_expander *s, t_env *env)
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

static int	handle_env_var_expansion(t_expander *s, t_env *env)
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

static void	handle_quotes(t_expander *s)
{
	if (s->str[s->i] == '\'' && !s->in_dquotes)
	{
		s->in_squotes = !s->in_squotes;
		s->i++;
	}
	else if (s->str[s->i] == '"' && !s->in_squotes)
	{
		s->in_dquotes = !s->in_dquotes;
		s->i++;
	}
}

static int	handle_dollar_expansion(t_expander *s, t_env *env)
{
	if (s->str[s->i] == '$' && s->str[s->i + 1] && !s->in_squotes)
	{
		if (s->str[s->i + 1] == '?')
		{
			handle_dollar_status(s, env);
			return (1);
		}
		if (handle_dollar_param_expansion(s))
			return (1);
	}
	if (s->str[s->i] == '$' && s->str[s->i + 1] && !s->in_squotes &&
			(ft_isalpha(s->str[s->i + 1]) || s->str[s->i + 1] == '_' || s->str[s->i + 1] == '$'))
	{
		if (!handle_env_var_expansion(s, env))
			return (-1);
		return (1);
	}
	return (0);
}

char *handle_dollar_expander(t_token *token, t_env *env)
{
	t_expander s;
	int		ret;

	s.in_squotes = 0;
	s.in_dquotes = 0;
	s.result = ft_strdup("");
	if (!s.result)
		return (NULL);
	s.str = token->value;
	s.i = 0;
	while (s.str[s.i])
	{
		if ((s.str[s.i] == '\'' && !s.in_dquotes) || (s.str[s.i] == '"' && !s.in_squotes))
		{
			handle_quotes(&s);
			continue;
		}
		ret = handle_dollar_expansion(&s, env);
		if (ret == 1)
			continue;
		else if (ret == -1)
			return (NULL);
		s.temp = s.result;
		s.result = ft_strjoin_char(s.result, s.str[s.i++]);
		free(s.temp);
		if (!s.result)
			return (NULL);
	}
	return (s.result);
}
