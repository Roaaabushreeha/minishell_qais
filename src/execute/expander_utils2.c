/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falhaimo <falhaimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:21:43 by falhaimo          #+#    #+#             */
/*   Updated: 2025/05/21 17:24:46 by falhaimo         ###   ########.fr       */
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
	char	*old_result;
	char	new_char[2];

	old_result = result;
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

void	copy_inside_quotes(const char *str, char *result, int *i, int *j)
{
	(*i)++;
	while (str[*i] && str[*i] != '"')
		result[(*j)++] = str[(*i)++];
	if (str[*i])
		(*i)++;
}

void	copy_outside_quotes(const char *str, char *result, int *i, int *j)
{
	result[(*j)++] = str[(*i)++];
}
