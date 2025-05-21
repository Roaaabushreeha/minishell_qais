/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabu-shr <rabu-shr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:56:46 by rabu-shr          #+#    #+#             */
/*   Updated: 2025/05/20 15:50:26 by rabu-shr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expand_echo_args(t_cmd *cmds, t_env *env)
{
	int		i;
	char	*expanded;
	t_token	token;

	i = 0;
	while (cmds->args[i])
	{
		token.value = cmds->args[i];
		expanded = handle_dollar_expander(&token, env);
		if (expanded)
		{
			free(cmds->args[i]);
			cmds->args[i] = expanded;
		}
		i++;
	}
}

static int	handle_echo(t_cmd *cmds)
{
	int	i;

	i = 1;
	while (cmds->args[i])
	{
		printf("%s", cmds->args[i]);
		if (cmds->args[i + 1])
			printf(" ");
		i++;
	}
	printf("\n");
	return (0);
}

static int	handle_env_commands(t_cmd *cmds, t_env *env)
{
	if (!ft_strcmp(cmds->args[0], "env"))
		env_print(env);
	else if (!ft_strcmp(cmds->args[0], "export"))
		export_command(cmds, &env);
	else if (!ft_strcmp(cmds->args[0], "unset"))
		unset_command(cmds, &env);
	return (0);
}

static int	handle_directory_commands(t_cmd *cmds, t_env *env)
{
	if (!ft_strcmp(cmds->args[0], "pwd"))
		return (handle_pwd());
	else if (!ft_strcmp(cmds->args[0], "cd"))
		cd_command(cmds, env);
	return (0);
}

int	builtin_commands(t_cmd *cmds, t_env *env, int *flag)
{
	int	result;

	result = 0;
	if (!ft_strcmp(cmds->args[0], "echo"))
		result = handle_echo(cmds);
	else if (!ft_strcmp(cmds->args[0], "pwd") || !ft_strcmp(cmds->args[0],
				"cd"))
		result = handle_directory_commands(cmds, env);
	else if (!ft_strcmp(cmds->args[0], "env") || !ft_strcmp(cmds->args[0],
				"export") || !ft_strcmp(cmds->args[0], "unset"))
		result = handle_env_commands(cmds, env);
	if (ft_strcmp(cmds->args[0], "pwd") != 0)
		*flag = 1;
	return (result);
}
