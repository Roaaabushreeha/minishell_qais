/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabu-shr <rabu-shr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:03:55 by rabu-shr          #+#    #+#             */
/*   Updated: 2025/05/14 18:51:45 by rabu-shr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	handle_heredoc_token(t_token *temp, t_token *next)
{
	free(temp->value);
	temp->value = ft_strdup("<<");
	temp->type = HEREDOC;
	temp->next = next->next;
	free(next->value);
	free(next);
}

static void	set_token_type(t_token *token)
{
	if (!ft_strcmp(token->value, "|"))
		token->type = PIPE;
	else if (!ft_strcmp(token->value, ">"))
		token->type = REDIRECT_OUT;
	else if (!ft_strcmp(token->value, "<"))
		token->type = REDIRECT_IN;
	else if (!ft_strcmp(token->value, ">>"))
		token->type = APPEND;
	else if (!ft_strcmp(token->value, "\""))
		token->type = DQUOTE;
	else if (!ft_strcmp(token->value, "\'"))
		token->type = SQUOTE;
	else
		token->type = WORD;
}

static void	process_token_list(t_token *temp)
{
	t_token	*next;

	while (temp && temp->next)
	{
		next = temp->next;
		if (temp->value[0] == '<' && next->value[0] == '<')
		{
			handle_heredoc_token(temp, next);
			temp = temp->next;
			continue ;
		}
		set_token_type(temp);
		temp = temp->next;
	}
	if (temp)
		set_token_type(temp);
}

void	get_built_in_type(t_token *token)
{
	process_token_list(token);
	define_word(token);
}
