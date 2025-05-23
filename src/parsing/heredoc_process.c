/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalqam <jalqam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:54:59 by rabu-shr          #+#    #+#             */
/*   Updated: 2025/05/21 18:13:03 by jalqam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*create_heredoc_filename(char *delimiter)
{
	char	*temp_filename;
	char	num[20];

	ft_memset(num, 0, sizeof(num));
	temp_filename = ft_calloc(100, sizeof(char));
	if (!temp_filename)
		return (NULL);
	ft_strlcpy(temp_filename, "/tmp/.tmp_", 13);
	ft_strlcat(temp_filename, num, 100);
	ft_strlcat(temp_filename, "_", 100);
	ft_strlcat(temp_filename, delimiter, 100);
	return (temp_filename);
}

static int	setup_heredoc(char *delimiter, t_cmd *cmd, char **clean_delim)
{
	char	*temp_filename;
	int		fd_heredoc;

	*clean_delim = clean_delimiter(delimiter);
	temp_filename = create_heredoc_filename(delimiter);
	if (!temp_filename)
		return (-1);
	if (cmd->temp)
	{
		free(cmd->temp);
		cmd->temp = NULL;
	}
	cmd->temp = ft_strdup(temp_filename);
	free(temp_filename);
	fd_heredoc = open(cmd->temp, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd_heredoc == -1)
	{
		free(*clean_delim);
		free(cmd->temp);
		cmd->temp = NULL;
		return (-1);
	}
	cmd->flag_heredoc = 1;
	return (fd_heredoc);
}

void	write_heredoc_expanded(int fd, char *buffer, char *expanded, t_env *env)
{
	expanded = expand_variables(buffer, env, 0);
	if (expanded)
	{
		write(fd, expanded, ft_strlen(expanded));
		write(fd, "\n", 1);
		free(expanded);
	}
}

static int	process_heredoc_input(int fd, char *delim, int quoted, t_env *env)
{
	char	*buffer;
	char	*trimmed;

	signal_handler(4);
	while (1)
	{
		buffer = readline("> ");
		if (check_heredoc_exit(buffer, env))
		{
			free(buffer);
			break ;
		}
		trimmed = ft_strtrim(buffer, "\n");
		if (ft_strcmp(trimmed, delim) == 0)
		{
			free(buffer);
			free(trimmed);
			break ;
		}
		free(trimmed);
		write_heredoc_line(fd, buffer, quoted, env);
	}
	return (0);
}

int	handle_heredoc(char *delimiter, t_cmd *cmd, t_env *env)
{
	int		fd_heredoc;
	char	*clean_delim;
	int		quoted;
	int		result;

	quoted = is_quoted_delimiter(delimiter);
	fd_heredoc = setup_heredoc(delimiter, cmd, &clean_delim);
	if (fd_heredoc == -1)
		return (1);
	result = process_heredoc_input(fd_heredoc, clean_delim, quoted, env);
	free(clean_delim);
	close(fd_heredoc);

	return (finalize_heredoc(cmd, env, result));
}