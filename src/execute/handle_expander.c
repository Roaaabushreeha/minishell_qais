/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expander.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalqam <jalqam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:00:36 by jalqam            #+#    #+#             */
/*   Updated: 2025/05/21 18:47:55 by jalqam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	append_char_to_result(char **result, char c)
// {
// 	char	*old_result;
// 	char	new_char[2];

// 	new_char[0] = c;
// 	new_char[1] = '\0';
// 	old_result = *result;
// 	*result = ft_strjoin(*result, new_char);
// 	free(old_result);
// 	return (*result == NULL);
// }

// char	*handle_mixed_quotes(t_token *token)
// {
// 	char	*result;
// 	char	*value;
// 	int		i;
// 	int		inside_double;
// 	int		inside_single;
// 	int		dollar_expansion;

// 	if (!token || !token->value)
// 		return (NULL);
// 	result = ft_strdup("");
// 	value = token->value;
// 	i = 0;
// 	inside_double = 0;
// 	inside_single = 0;
// 	dollar_expansion = 0;
// 	while (value[i])
// 	{
// 		if (value[i] == '\'' && value[i + 1] && value[i + 1] == '$'
				// && !inside_double)
// 		{
// 			if (append_char_to_result(&result, value[i++]))
// 				return (NULL);
// 			dollar_expansion = 1;
// 			continue ;
// 		}
// 		else if (value[i] == '\'' && !inside_double)
// 		{
// 			if (!dollar_expansion)
// 			{
// 				inside_single = !inside_single;
// 				if (append_char_to_result(&result, value[i++]))
// 					return (NULL);
// 				continue ;
// 			}
// 			dollar_expansion = 0;
// 		}
// 		else if (value[i] == '"' && !inside_single)
// 		{
// 			inside_double = !inside_double;
// 			i++;
// 			continue ;
// 		}
// 		if (append_char_to_result(&result, value[i++]))
// 			return (NULL);
// 	}
// 	return (result);
// }

// char	*handle_twoquotes(t_token *token)
// {
// 	char	*str;
// 	char	*result;
// 	int		i;
// 	int		j;

// 	str = ft_strdup(token->value);
// 	result = malloc(ft_strlen(str) + 1);
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

// int	handle_single_quote_char(char c, int *inside_quotes, int *i)
// {
// 	if (c == '\'')
// 	{
// 		*inside_quotes = !*inside_quotes;
// 		(*i)++;
// 		return (1);
// 	}
// 	return (0);
// }

// int	append_char_to_string(char **result, char c)
// {
// 	char	*old_result;
// 	char	new_char[2];

// 	new_char[0] = c;
// 	new_char[1] = '\0';
// 	old_result = *result;
// 	*result = ft_strjoin(*result, new_char);
// 	free(old_result);
// 	return (*result == NULL);
// }
