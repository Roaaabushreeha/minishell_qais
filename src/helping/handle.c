/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalqam <jalqam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 19:00:20 by jalqam            #+#    #+#             */
/*   Updated: 2025/05/20 15:52:42 by jalqam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_redirection(char *command, int i)
{
	if (command[i] == '>' && command[i + 1] == '\0')
	{
		text_error(0);
		return (1);
	}
	return (0);
}

static int	check_echo_format(char *command, int i, int flag_echo)
{
	if ((!flag_echo && command[i] == 'e' && command[i + 1] == 'c' && command[i
				+ 2] == 'h' && command[i + 3] == 'o') && command[i + 4] != ' '
		&& command[i + 5])
	{
		text_error(1);
		return (1);
	}
	return (0);
}

static int	check_pipe_syntax(char *command, int i)
{
	if ((command[i] == '|' && command[i + 1] == '|') || (command[i] == '|'
			&& (!command[i - 1] || !command[i + 1])))
	{
		printf("syntax error near unexpected token `|'\n");
		return (1);
	}
	return (0);
}

static int	check_heredoc_syntax(char *command, int i)
{
	if ((command[i] == '<' && command[i + 1] == '<') && (command[i + 2] == '<'
			|| !command[i + 2] || (command[i + 2] == ' ' && !command[i + 3])))
	{
		text_error(0);
		return (1);
	}
	return (0);
}

int	right_command_check(char *command)
{
	int	i;
	int	flag_echo;

	flag_echo = 0;
	i = 0;
	while (command[i])
	{
		if (command[i] == '"')
			flag_echo = 1;
		if (check_redirection(command, i) || check_echo_format(command, i,
				flag_echo) || check_pipe_syntax(command, i)
			|| check_heredoc_syntax(command, i))
			return (1);
		i++;
	}
	return (0);
}
