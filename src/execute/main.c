/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabu-shr <rabu-shr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:31:38 by jalqam            #+#    #+#             */
/*   Updated: 2025/05/20 18:21:45 by rabu-shr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*getpwd(char *prompt)
{
	char	*pwd;
	char	*temp;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_printf("Error: getcwd\n");
		return (NULL);
	}
	temp = ft_strjoin("🎀minishell:", pwd);
	prompt = ft_strjoin(temp, "$ ");
	free(temp);
	free(pwd);
	return (prompt);
}

void	free_envp(t_env *env)
{
	t_env	*temp;

	while (env)
	{
		temp = env;
		env = env->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
}

void	cleanup_iteration(char *readline_shell, char *pwd, t_token *tokens,
		t_cmd *cmd)
{
	if (readline_shell)
		free(readline_shell);
	if (pwd)
		free(pwd);
	if (tokens)
	{
		free_tokens(tokens);
	}
	if (cmd)
	{
		clean_files(cmd);
		free_commands(cmd);
	}
}

int	init_minishell(int argc, char *argv[], char *envp[], t_env **env)
{
	(void)argc;
	(void)argv;
	*env = init_envp(envp);
	if (!*env)
		return (1);
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_env	*env;
	char	*readline_shell;

	if (init_minishell(argc, argv, envp, &env))
		return (1);
	while (1)
	{
		signal_handler(0);
		env->pwd = getpwd(NULL);
		readline_shell = readline(env->pwd);
		if (!readline_shell)
		{
			g_signals_status = env->exit_status;
			handle_null_readline(env, readline_shell);
			exit(g_signals_status);
		}
		if (*readline_shell)
			add_history(readline_shell);
		if (process_input(readline_shell, env))
			continue ;
	}
	return (0);
}
