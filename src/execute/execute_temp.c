/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_temp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalqam <jalqam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 13:41:57 by rabu-shr          #+#    #+#             */
/*   Updated: 2025/05/19 13:47:18 by jalqam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_single_builtin(t_cmd *cmds, t_env *env, t_token *token, int *flag)
{
	int	status;
	int	count;

	status = 0;
	count = num_pip(token);
	while (cmds)
	{
		if (count == 0)
		{
			if (is_builtin_commands(cmds))
				status = builtin_commands(cmds, env, flag);
			break ;
		}
		cmds = cmds->next;
	}
	return (status);
}

int	save_stdout_and_redirect(t_cmd *cmds, int *saved_stdout)
{
	*saved_stdout = dup(STDOUT_FILENO);
	if (*saved_stdout == -1)
	{
		perror("minishell: dup error");
		return (1);
	}
	if (cmds && cmds->fd_out != -1)
	{
		if (dup2(cmds->fd_out, STDOUT_FILENO) == -1)
		{
			perror("minishell: dup2 error");
			close(*saved_stdout);
			return (1);
		}
	}
	return (0);
}
