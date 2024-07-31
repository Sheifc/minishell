#include "minishell.h"

static int	isnum(char *str)
{
	if (!str || str == (void *)0)
		return (-1);
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (!ft_isdigit((unsigned char)*str))
			return (0);
		str++;
	}
	return (1);
}

void	ft_exit(t_cmd *cmd)
{
	int		exit_code;
	long	num;

	exit_code = 1;
	if (cmd->n_args > 2)
	{
		ft_putendl_fd("exit: too many arguments", 2);
		exit_code = 1;
	}
	else if (cmd->n_args == 2)
	{
		if (isnum(cmd->arg[1]) == 0)
		{
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(cmd->arg[1], 2);
			ft_putendl_fd(": numeric argument required", 2);
			exit(255);
		}
		errno = 0;
		num = ft_atol(cmd->arg[1]);
		if (errno == ERANGE || num > LONG_MAX || num < LONG_MIN)
		{
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(cmd->arg[1], 2);
			ft_putendl_fd(": numeric argument required", 2);
			exit(255);
		}
		exit_code = (int)(num % 256);
	}
	printf("exit\n");
	exit(exit_code);
}
