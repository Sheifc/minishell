#include "minishell.h"

// this 2 functions are not gonna be used for the project that ones to use are gonna be the ones in the comments bellow, 
//commented only for incompatibilities with my mac
void	sigint_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		// rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	init_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

/* extern int	g_sig;

void	heredoc_handler(int signum)
{
	(void)signum;
	exit(130);
}

void	signal_d(t_shell *data)
{
	free_all(data);
	printf("exit\n");
	exit(data->status);
}

void	signal_c(int signal)
{
	(void)signal;
	if (g_sig == 1)
	{
		write(1, "\033[K\n", 5);
		//rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (g_sig == 0)
	{
		rl_on_new_line();
		//rl_replace_line("", 0);
		rl_redisplay();
		write(1, "\033[K\n", 5);
		rl_on_new_line();
		//rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	signal_quit(int signal)
{
	(void)signal;
	write(2, "Quit (core dumped)\n", 20);
}

void	init_signals(void)
{
	signal(SIGTSTP, SIG_IGN);
	if (g_sig == 0)
		signal(SIGQUIT, SIG_IGN);
	else
		signal(SIGQUIT, signal_quit);
	signal(SIGINT, signal_c);
} */
