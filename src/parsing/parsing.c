/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalqam <jalqam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:15:26 by jalqam            #+#    #+#             */
/*   Updated: 2025/05/21 18:13:07 by jalqam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	define_word(t_token *token)
{
	t_token	*temp;
	int		flag;

	temp = token;
	flag = 1;
	while (temp)
	{
		if (temp->type == WORD)
		{
			if (flag == 1 || flag == PIPE)
				temp->type = COMMAND;
			else if (flag == REDIRECT_IN)
				temp->type = INFILE;
			else if (flag == REDIRECT_OUT || flag == APPEND)
				temp->type = OUTFILE;
			else
				temp->type = ARGS;
			flag = 0;
		}
		else if (temp->type == PIPE || temp->type == REDIRECT_IN
			|| temp->type == REDIRECT_OUT || temp->type == APPEND)
			flag = temp->type;
		temp = temp->next;
	}
}
int	cleanup_temp_and_return(t_cmd *cmd, int ret)
{
	if (cmd->temp)
	{
		unlink(cmd->temp);
		free(cmd->temp);
		cmd->temp = NULL;
	}
	return (ret);
}

int	finalize_heredoc(t_cmd *cmd, t_env *env, int result)
{
	cmd->fd_in = open(cmd->temp, O_RDONLY);
	if (cmd->fd_in == -1)
		return (cleanup_temp_and_return(cmd, 1));
	if (result || g_signals_status == 130)
	{
		if (g_signals_status == 130)
		{
			env->exit_status = g_signals_status;
			g_signals_status = 0;
		}
		return (cleanup_temp_and_return(cmd, 1));
	}
	return (0);
}