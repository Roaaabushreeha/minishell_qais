/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalqam <jalqam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:35:05 by jalqam            #+#    #+#             */
/*   Updated: 2025/05/21 18:54:38 by jalqam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo_command(t_cmd *cmds, t_env *env)
{
	int	i;
	int	no_newline;

	if (!cmds || !cmds->args)
		return ;
	i = 1;
	no_newline = 0;
	if (cmds->args[i] && ft_strcmp(cmds->args[i], "-n") == 0)
	{
		no_newline = 1;
		i++;
	}
	while (cmds->args[i])
	{
		ft_putstr_fd(cmds->args[i], STDOUT_FILENO);
		if (cmds->args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (!no_newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
	env->exit_status = 0;
}
