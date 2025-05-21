/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabu-shr <rabu-shr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:27:15 by rabu-shr          #+#    #+#             */
/*   Updated: 2025/05/14 17:05:41 by rabu-shr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_result(char **result, size_t j)
{
	while (j > 0)
		free(result[--j]);
	free(result);
}

void	skip_spaces(char *str, size_t *i)
{
	while (str[*i] == ' ')
		(*i)++;
}

void	handle_quotes(char *str, size_t *i, int *in_quotes, char *quote_char)
{
	*in_quotes = 1;
	*quote_char = str[*i];
	(*i)++;
}

void	init_split_vars(t_split *s, char *word)
{
	s->i = 0;
	s->j = 0;
	s->in_quotes = 0;
	s->quote_char = 0;
	s->new_word = malloc(ft_strlen(word) * 3 + 1);
	if (!s->new_word)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	s->word_splitted = NULL;
}
