/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 19:24:38 by sheferna          #+#    #+#             */
/*   Updated: 2024/08/23 19:24:39 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>

int		g_sig = 0;

void	sigint_handler(int signal)
{
	(void)signal;
	if (g_sig == 1)
	{
		write(1, "\033[K\n", 5);
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (g_sig == 0)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		write(1, "\033[K\n", 5);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	signal_d(t_shell *data)
{
	free_all(data);
	printf("exit\n");
	exit(data->status);
}

void	signal_quit(int signal)
{
	if (signal == SIGQUIT)
	{
		write(2, "Quit (core dumped)\n", 20);
	}
}

void	sigchld_handler(int signum)
{
	(void)signum;
	while (waitpid(-1, NULL, WNOHANG) > 0)
		;
}

void	init_signals(void)
{
	signal(SIGTSTP, SIG_IGN);
	if (g_sig == 0)
		signal(SIGQUIT, SIG_IGN);
	else
		signal(SIGQUIT, signal_quit);
	signal(SIGINT, sigint_handler);
	signal(SIGCHLD, sigchld_handler);
}
