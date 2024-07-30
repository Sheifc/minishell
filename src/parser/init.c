#include "minishell.h"

void	init_struct(t_shell *data, char **envp)
{
	data->token = NULL;
	data->cmd = NULL;
    data->env = NULL;
    data->export = NULL;
    data->prompt = NULL;
    data->envp = envp;
    data->path = NULL;
    data->status = 0;
    data->pid = 0;
    data->cmd_count = 0;
}

void	sigint_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		//rl_replace_line("", 0);
		rl_redisplay();
	}
}

void    init_signals()
{
    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
}

void    init(t_shell *data, char **envp)
{
    init_signals();
    init_struct(data, envp);
    init_env(data, envp);
}

/* 
extern int	g_sig;

void	heredoc_handler(int signum)
{
	(void)signum;
	exit(130);
}

void	signal_d(t_shell *data)
{
	free_data(data);
	free_env_node(&data->env);
	free_env_node(&data->export);
	printf("exit\n");
	exit(data->status);
}

void	signal_c(int signal)
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

void	signal_quit(int signal)
{
	(void)signal;
	write(2, "Quit (core dumped)\n", 20);
}

void	init_signal(void)
{
	signal(SIGTSTP, SIG_IGN);
	if (g_sig == 0)
		signal(SIGQUIT, SIG_IGN);
	else
		signal(SIGQUIT, signal_quit);
	signal(SIGINT, signal_c);
}
*/