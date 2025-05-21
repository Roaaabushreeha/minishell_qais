/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_state.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabu-shr <rabu-shr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:04:49 by jalqam            #+#    #+#             */
/*   Updated: 2025/05/21 15:37:24 by rabu-shr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*handle_dollar_param(char *str, int *i)
{
	int	start;

	if (str[*i] == '$' && str[*i + 1])
	{
		(*i)++;
		if (str[*i] == '0')
		{
			(*i)++;
			return (ft_strdup("minishell"));
		}
		else if (str[*i + 1] && ft_isdigit(str[*i + 1]))
		{
			(*i) += 1;
			start = *i;
			while (str[*i] && ft_isdigit(str[*i]))
				(*i)++;
			return (ft_substr(str, start, *i - start));
		}
		(*i)--;
	}
	return (NULL);
}

