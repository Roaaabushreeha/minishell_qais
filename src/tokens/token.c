/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabu-shr <rabu-shr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:01:41 by jalqam            #+#    #+#             */
/*   Updated: 2025/05/14 17:07:04 by rabu-shr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*new_token(char *value)
{
	t_token	*token;
	char	*dup_value;

	if (!value)
		return (NULL);
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	dup_value = ft_strdup(value);
	if (!dup_value)
	{
		free(token);
		return (NULL);
	}
	token->value = dup_value;
	token->type = 0;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

t_token	*tokenize(char *input)
{
	t_token	*tokens;
	char	**token_split;
	int		i;

	tokens = NULL;
	if (!input)
		return (NULL);
	token_split = our_split(input);
	if (!token_split)
		return (NULL);
	i = -1;
	while (token_split[++i])
	{
		add_token(&tokens, token_split[i]);
		if (!tokens)
		{
			free_tokens_split(token_split);
			return (NULL);
		}
	}
	free_tokens_split(token_split);
	return (tokens);
}

void	add_token(t_token **head, char *value)
{
	t_token	*new;
	t_token	*temp;

	new = new_token(value);
	if (!new)
	{
		if (*head)
			free_tokens(*head);
		*head = NULL;
		return ;
	}
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	new->prev = temp;
}

void	free_tokens(t_token *head)
{
	t_token	*next;

	while (head)
	{
		next = head->next;
		if (head->value)
		{
			free(head->value);
			head->value = NULL;
		}
		free(head);
		head = next;
	}
	free(head);
	head = NULL;
}
