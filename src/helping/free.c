/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabu-shr <rabu-shr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:49:36 by jalqam            #+#    #+#             */
/*   Updated: 2025/05/17 14:28:39 by rabu-shr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_commands(t_cmd *cmd)
{
	t_cmd	*next;
	int		i;

	while (cmd)
	{
		next = cmd->next;
		i = 0;
		while (cmd->args && cmd->args[i])
		{
			free(cmd->args[i]);
			i++;
		}
		if (cmd->args)
			free(cmd->args);
		if (cmd->temp)
		{
			unlink(cmd->temp);
			free(cmd->temp);
		}
		free(cmd);
		cmd = next;
	}
	free(cmd);
}

void	cleanup_and_exit(t_token *tokens, t_cmd *cmd, t_env *env, int exit_code)
{
	if (tokens)
		free_tokens(tokens);
	if (cmd)
		free_commands(cmd);
	if (env)
	{
		if (env->pwd)
			free(env->pwd);
		free_env_list(env);
	}
	exit(exit_code);
}

void	free_function(char **s_cmd, char **paths)
{
	ft_free(s_cmd);
	ft_free(paths);
}

void	free_tokens_split(char **token_split)
{
	int	i;

	i = 0;
	while (token_split[i])
		free(token_split[i++]);
	free(token_split);
}
