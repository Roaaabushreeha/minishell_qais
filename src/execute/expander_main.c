/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalqam <jalqam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:52:32 by rabu-shr          #+#    #+#             */
/*   Updated: 2025/05/21 19:18:41 by jalqam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_dollar_case(t_token *temp, t_env *env)
{
	char	*expanded;

	expanded = handle_dollar_expander(temp, env);
	if (expanded)
	{
		free(temp->value);
		temp->value = expanded;
		return (1);
	}
	return (0);
}

int	handle_quotes_case(t_token *temp)
{
	char	*expanded;

	expanded = handle_mixed_quotes(temp);
	if (expanded)
	{
		free(temp->value);
		temp->value = expanded;
		return (1);
	}
	return (0);
}

int	expander_main(t_token *token, t_env *env)
{
	t_token	*temp;

	temp = token;
	while (temp)
	{
		if (!temp->value)
		{
			temp = temp->next;
			continue ;
		}
		if (ft_strchr(temp->value, '$'))
			handle_dollar_case(temp, env);
		else if (ft_strchr(temp->value, '"') || ft_strchr(temp->value, '\''))
			handle_quotes_case(temp);
		temp = temp->next;
	}
	return (0);
}
