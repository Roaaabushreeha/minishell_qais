/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_temp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabu-shr <rabu-shr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:19:43 by rabu-shr          #+#    #+#             */
/*   Updated: 2025/05/20 16:26:38 by rabu-shr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_null_readline(t_env *env, char *readline_shell)
{
	(void)readline_shell;
	ft_printf("exit\n");
	free(env->pwd);
	free_env_list(env);
	return (1);
}

int	execute_and_cleanup(char *readline_shell, t_env *env, t_token *tokens)
{
	t_cmd	*cmd;
	int		status;

	cmd = separator(tokens, env);
	if (!cmd)
	{
		if (env->pwd)
			free(env->pwd);
		return (1);
	}
	status = execute_commands(cmd, env, tokens);
	cleanup_iteration(readline_shell, env->pwd, tokens, cmd);
	if (status)
		env->exit_status = status;
	else if (env->exit_status == 0)
		env->exit_status = 0;
	return (0);
}

int	process_input(char *readline_shell, t_env *env)
{
	t_token	*tokens;

	if (right_command_check(readline_shell))
		return (cleanup_iteration(readline_shell, env->pwd, NULL, NULL), 1);
	tokens = tokenize(readline_shell);
	if (!tokens)
		return (cleanup_iteration(readline_shell, env->pwd, NULL, NULL), 1);
	get_built_in_type(tokens);
	if (!tokens)
		return (cleanup_iteration(readline_shell, env->pwd, NULL, NULL), 1);
	if (check_quotes_num(tokens))
		return (cleanup_iteration(readline_shell, env->pwd, tokens, NULL), 1);
	return (execute_and_cleanup(readline_shell, env, tokens));
}
