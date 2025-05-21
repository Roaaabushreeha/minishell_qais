/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabu-shr <rabu-shr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:46:13 by jalqam            #+#    #+#             */
/*   Updated: 2025/05/19 15:14:31 by rabu-shr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	split_quotes(char c, int *in_quotes, char *quote_char)
{
	if ((c == '"' || c == '\'') && *in_quotes == 0)
	{
		*in_quotes = 1;
		*quote_char = c;
	}
	else if (c == *quote_char)
		*in_quotes = 0;
}

void	split_chars(char *word, char *new_word, size_t *i, size_t *j)
{
	if (word[*i] == '|' || word[*i] == '>' || word[*i] == '<')
	{
		if (*i > 0 && word[*i - 1] != ' ')
			new_word[(*j)++] = ' ';
		new_word[(*j)++] = word[*i];
		if (word[*i] == '>' && word[*i + 1] == '>')
		{
			(*i)++;
			new_word[(*j)++] = '>';
		}
		if (word[*i + 1] != ' ' && word[*i + 1] != '\0' && word[*i + 1] != '>')
			new_word[(*j)++] = ' ';
	}
	else
		new_word[(*j)++] = word[*i];
}

char	**our_split(char *word)
{
	t_split	s;

	if (!word)
		return (NULL);
	init_split_vars(&s, word);
	if (!s.new_word)
		return (NULL);
	while (word[s.i])
	{
		split_quotes(word[s.i], &s.in_quotes, &s.quote_char);
		if (!s.in_quotes)
			split_chars(word, s.new_word, &s.i, &s.j);
		else
			s.new_word[s.j++] = word[s.i];
		s.i++;
	}
	s.new_word[s.j] = '\0';
	s.word_splitted = split_with_quotes(s.new_word);
	free(s.new_word);
	return (s.word_splitted);
}

char	*extract_word(char *str, size_t *i)
{
	size_t	start;
	int		in_quotes;
	char	quote_char;

	start = *i;
	in_quotes = 0;
	quote_char = 0;
	while (str[*i] && (in_quotes || str[*i] != ' '))
	{
		if ((str[*i] == '"' || str[*i] == '\'') && !in_quotes)
		{
			quote_char = str[*i];
			in_quotes = 1;
			(*i)++;
			continue ;
		}
		else if (str[*i] == quote_char && in_quotes)
		{
			in_quotes = 0;
			(*i)++;
			continue ;
		}
		(*i)++;
	}
	return (ft_substr(str, start, *i - start));
}

char	**split_with_quotes(char *str)
{
	char	**result;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	result = malloc(sizeof(char *) * (ft_strlen(str) + 1));
	if (!result)
		return (NULL);
	while (str[i])
	{
		skip_spaces(str, &i);
		if (!str[i])
			break ;
		result[j] = extract_word(str, &i);
		if (!result[j])
		{
			free_result(result, j);
			return (NULL);
		}
		j++;
	}
	result[j] = NULL;
	return (result);
}
