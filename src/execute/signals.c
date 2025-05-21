/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalqam <jalqam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 13:09:31 by jalqam            #+#    #+#             */
/*   Updated: 2025/05/19 16:07:37 by jalqam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

volatile sig_atomic_t	g_signals_status = 0;

void	sigint_handler(int sig)
{
	if (sig)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_signals_status = sig;
	}
}

void	child_signal(int sig)
{
	if (sig == SIGINT)
	{
		g_signals_status = 130;
		write(1, "\n", 1);
	}
	else if (sig == SIGQUIT)
		g_signals_status = 131;
}

void	signal_nnl(int sig)
{
	g_signals_status = sig;
	write(1, "\n", 1);
}
void	signal_red(int sig)
{
	g_signals_status = sig;
	write(1, "\n", 1);
	close(0);
}

void	signal_handler(int mode)
{
	if (mode == 0)
	{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == 1)
	{
		signal(SIGINT, child_signal);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (mode == 3)
	{
		signal(SIGINT, signal_nnl);
		signal(SIGQUIT, SIG_IGN);
	}
	if (mode == 4)
	{
		signal(SIGINT, signal_red);
		signal(SIGQUIT, SIG_IGN);
	}
}
