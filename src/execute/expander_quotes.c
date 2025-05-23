/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalqam <jalqam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:03:34 by jalqam            #+#    #+#             */
/*   Updated: 2025/05/21 18:02:38 by jalqam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	skip_leading_spaces(char *str, int *i)
{
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
		(*i)++;
}