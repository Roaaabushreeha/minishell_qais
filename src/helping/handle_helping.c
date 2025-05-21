/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_helping.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalqam <jalqam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:19:28 by jalqam            #+#    #+#             */
/*   Updated: 2025/05/19 16:19:41 by jalqam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	text_error(int which)
{
	if (which == 0)
	{
		ft_printf("syntax error near unexpected token `newline'\n");
		return ;
	}
	else if (which == 1)
	{
		ft_printf("command not found\n");
		return ;
	}
}

void	handle_quote_states(char c, int *in_double, int *in_single)
{
	if (c == '"')
	{
		if (!*in_single)
			*in_double = !*in_double;
	}
	else if (c == '\'')
	{
		if (!*in_double)
			*in_single = !*in_single;
	}
}

int	check_token_quotes(t_token *temp)
{
	int	i;
	int	in_double;
	int	in_single;

	i = 0;
	in_double = 0;
	in_single = 0;
	while (temp->value && temp->value[i])
	{
		handle_quote_states(temp->value[i], &in_double, &in_single);
		i++;
	}
	return ((in_single && !in_double) || (!in_single && in_double));
}

int	check_quotes_num(t_token *token)
{
	t_token	*temp;

	temp = token;
	while (temp)
	{
		if (check_token_quotes(temp))
			return (1);
		temp = temp->next;
	}
	return (0);
}
