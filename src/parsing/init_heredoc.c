/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabu-shr <rabu-shr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:03:50 by rabu-shr          #+#    #+#             */
/*   Updated: 2025/05/18 18:13:40 by rabu-shr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_heredoc_redirection(t_token *token, t_cmd *cmd, t_env *env)
{
	int	result;

	result = handle_heredoc(token->next->value, cmd, env);
	free(token->value);
	token->value = NULL;
	return (result);
}

int	handle_input_redirect(t_token *token, t_cmd *cmd)
{
	int	result;

	result = init_handle_input_redirection(cmd, token->next->value);
	if (token->value)
	{
		free(token->value);
		token->value = NULL;
	}
	return (result);
}

int	handle_output_redirect(t_token *token, t_cmd *cmd, int is_append)
{
	int	result;

	result = init_handle_output_redirection(cmd, token->next->value, is_append);
	if (token->value && !is_append)
	{
		free(token->value);
		token->value = NULL;
	}
	return (result);
}

int	initredirction(t_token *token, t_cmd *cmd, t_env *env)
{
	if (init_validate_redirection(token))
		return (1);
	if (ft_strcmp(token->value, "<<") == 0)
		return (handle_heredoc_redirection(token, cmd, env));
	if (ft_strcmp(token->value, "<") == 0)
		return (handle_input_redirect(token, cmd));
	if (ft_strcmp(token->value, ">") == 0)
		return (handle_output_redirect(token, cmd, 0));
	if (ft_strcmp(token->value, ">>") == 0)
		return (handle_output_redirect(token, cmd, 1));
	return (0);
}
