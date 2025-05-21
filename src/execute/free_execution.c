/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabu-shr <rabu-shr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:45:30 by rabu-shr          #+#    #+#             */
/*   Updated: 2025/05/20 16:05:12 by rabu-shr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cleanup_heredocs(t_cmd *temp)
{
	while (temp)
	{
		if (temp->flag_heredoc && temp->temp)
		{
			unlink(temp->temp);
			free(temp->temp);
			temp->temp = NULL;
		}
		temp = temp->next;
	}
}

void	wait_for_children(int count)
{
	while (count-- > 0)
		waitpid(-1, NULL, 0);
}

void	cleanup_resources(t_env *env, t_token *tokens, t_cmd *cmd)
{
	if (env && env->pwd)
		free(env->pwd);
	if (tokens)
		free_tokens(tokens);
	if (cmd)
		free_commands(cmd);
	if (env)
		free_env_list(env);
	exit(1);
}
