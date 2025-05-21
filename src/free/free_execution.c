/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalqam <jalqam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:45:30 by rabu-shr          #+#    #+#             */
/*   Updated: 2025/05/19 18:25:32 by jalqam           ###   ########.fr       */
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
	if (env)
		free_env_list(env);
	if (tokens)
		free_tokens(tokens);
	if (cmd)
		free_commands(cmd);
	if (env->pwd)
		free(env->pwd);
	exit(1);
}
