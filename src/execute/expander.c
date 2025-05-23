/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalqam <jalqam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:43:00 by rabu-shr          #+#    #+#             */
/*   Updated: 2025/05/21 18:02:31 by jalqam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	append_cleaned_word(char *str, char *result, int *i, int *j)
{
	int	space;

	space = 0;
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
		(ft_isalpha(s->str[s->i + 1]) || s->str[s->i + 1] == '_' || s->str[s->i
				+ 1] == '$'))
	{
		if (!handle_env_var_expansion(s, env))
			return (-1);
		return (1);
	}
	return (0);
}

char	*handle_dollar_expander(t_token *token, t_env *env)
{
	t_expander	s;
	int			ret;

	s.in_squotes = 0;
	s.in_dquotes = 0;
	s.result = ft_strdup("");
	if (!s.result)
		return (NULL);
	s.str = token->value;
	s.i = 0;
	while (s.str[s.i])
	{
		if ((s.str[s.i] == '\'' && !s.in_dquotes) || (s.str[s.i] == '"'
				&& !s.in_squotes))
		{
			handle_quotes(&s);
			continue ;
		}
		ret = handle_dollar_expansion(&s, env);
		if (ret == 1)
			continue ;
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
