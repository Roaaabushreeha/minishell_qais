/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabu-shr <rabu-shr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:50:30 by rabu-shr          #+#    #+#             */
/*   Updated: 2025/05/14 16:50:26 by rabu-shr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_quoted_delimiter(char *d)
{
	int	result;
	int	l;

	l = ft_strlen(d);
	result = ((d[0] == '"' && d[l - 1] == '"') || (d[0] == '\'' && d[l
				- 1] == '\''));
	return (result);
}

char	*clean_delimiter(char *delimiter)
{
	int		len;
	char	*clean;

	if (!is_quoted_delimiter(delimiter))
		return (ft_strdup(delimiter));
	len = ft_strlen(delimiter);
	clean = ft_substr(delimiter, 1, len - 2);
	return (clean);
}

int	init_handle_input_redirection(t_cmd *cmd, const char *filename)
{
	if (cmd->fd_in != -1)
		close(cmd->fd_in);
	cmd->fd_in = open(filename, O_RDONLY);
	if (cmd->fd_in == -1)
	{
		printf("minishell: %s: No such file or directory\n", filename);
		return (1);
	}
	return (0);
}

int	init_handle_output_redirection(t_cmd *cmd, const char *filename,
		int is_append)
{
	int	flags;

	if (cmd->fd_out != -1)
		close(cmd->fd_out);
	if (is_append)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	cmd->fd_out = open(filename, flags, 0644);
	if (cmd->fd_out == -1)
	{
		printf("minishell: %s: Permission denied\n", filename);
		return (1);
	}
	return (0);
}

int	init_validate_redirection(t_token *token)
{
	if (!token || !token->next || !token->next->value)
	{
		printf("Error: Invalid redirection syntax\n");
		return (1);
	}
	return (0);
}
