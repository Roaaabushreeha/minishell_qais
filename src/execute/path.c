/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalqam <jalqam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:52:18 by rabu-shr          #+#    #+#             */
/*   Updated: 2025/05/20 19:53:07 by jalqam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*check_direct_path(char *cmd, t_env *env)
{
	if (cmd[0] == '/')
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (ft_strdup(cmd));
		env->exit_status = 127;
	}
	else if (cmd[0] == '.')
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (ft_strdup(cmd));
		env->exit_status = 126;
	}
	return (NULL);
}

static char	*find_executable_path(char **paths, char **s_cmd)
{
	int		i;
	char	*path_part;
	char	*exec;

	i = -1;
	while (paths[++i])
	{
		path_part = ft_strjoin(paths[i], "/");
		exec = ft_strjoin(path_part, s_cmd[0]);
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
			return (exec);
		free(exec);
	}
	return (NULL);
}

char	*get_path_from_env(char *cmd, t_env *env)
{
	t_env	*path_env;
	char	**paths;
	char	**s_cmd;
	char	*exec;

	exec = check_direct_path(cmd, env);
	if (exec)
		return (exec);
	path_env = find_env_node("PATH", env);
	if (!path_env || !path_env->value)
	{
		ft_printf("DEBUG: PATH not found or empty\n");
		return (NULL);
	}
	paths = ft_split(path_env->value, ':');
	if (!paths)
		return (NULL);
	s_cmd = ft_split(cmd, ' ');
	exec = find_executable_path(paths, s_cmd);
	free_function(s_cmd, paths);
	return (exec);
}

char	*my_env(const char *key, char **envp)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		sub = ft_substr(envp[i], 0, j);
		if (ft_strncmp(sub, key, ft_strlen(key)) == 0)
		{
			free(sub);
			return (envp[i] + j + 1);
		}
		free(sub);
		i++;
	}
	return (NULL);
}
