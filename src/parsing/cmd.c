/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabu-shr <rabu-shr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:59:17 by rabu-shr          #+#    #+#             */
/*   Updated: 2025/05/18 18:03:36 by rabu-shr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = ft_calloc(100, sizeof(char *));
	if (!cmd->args)
	{
		free(cmd);
		return (NULL);
	}
	cmd->command_num = 0;
	cmd->cmd_count = 0;
	cmd->type = NULL;
	cmd->next = NULL;
	cmd->pid = 0;
	cmd->prev = -1;
	cmd->flag_heredoc = 0;
	cmd->fd_in = -1;
	cmd->fd_out = -1;
	return (cmd);
}

int	is_redirect(char *value)
{
	int	result;

	result = (ft_strcmp(value, "<") == 0 || ft_strcmp(value, ">") == 0
			|| ft_strcmp(value, ">>") == 0 || ft_strcmp(value, "<<") == 0);
	return (result);
}

void	ft_free_current_token(t_token **token)
{
	t_token	*current;
	t_token	*next;
	t_token	*prev;

	if (!*token)
		return ;
	current = *token;
	next = current->next;
	prev = current->prev;
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
	if (current->value)
		free(current->value);
	free(current);
	*token = next;
}

int	handle_redirection(t_token **token, t_cmd *new_cmd, t_env *env)
{
	if (!(*token)->next || !(*token)->next->value)
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	if (initredirction(*token, new_cmd, env))
	{
		return (1);
	}
	*token = (*token)->next->next;
	return (0);
}

char	*process_command_arg(t_token *token, int is_first_arg, t_env *env)
{
	char	*processed_value;

	processed_value = NULL;
	if (is_first_arg)
	{
		expander_main(token, env);
		processed_value = ft_strdup(token->value);
		if (!processed_value)
			return (NULL);
	}
	else if (ft_strchr(token->value, '\'') && ft_strchr(token->value, '"'))
	{
		processed_value = handle_mixed_quotes(token);
		if (!processed_value)
			return (NULL);
	}
	else
	{
		processed_value = ft_strdup(token->value);
		if (!processed_value)
			return (NULL);
	}
	return (processed_value);
}
