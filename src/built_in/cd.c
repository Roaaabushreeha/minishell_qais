/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalqam <jalqam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:20:55 by jalqam            #+#    #+#             */
/*   Updated: 2025/05/20 19:44:40 by jalqam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	handle_home_directory(t_env *env, t_env *home)
{
	if (!home)
	{
		ft_printf("minishell: cd: HOME not set\n");
		env->exit_status = 1;
		return (1);
	}
	if (chdir(home->value) == -1)
	{
		perror("minishell: cd");
		env->exit_status = 1;
		return (1);
	}
	return (0);
}

static int	handle_directory_change(t_env *env, const char *path)
{
	if (chdir(path) == -1)
	{
		perror("minishell: cd");
		env->exit_status = 1;
		return (1);
	}
	env->exit_status = 0;
	return (0);
}

int	cd_command(t_cmd *cmds, t_env *env)
{
	t_env	*home;

	if (!cmds->args[1] || cmds->args[1][0] == '~')
	{
		home = find_env_node("HOME", env);
		return (handle_home_directory(env, home));
	}
	if (cmds->args[2])
	{
		ft_printf("minishell: cd: too many arguments\n");
		env->exit_status = 1;
		return (1);
	}
	return (handle_directory_change(env, cmds->args[1]));
}
