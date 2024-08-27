/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 19:22:47 by sheferna          #+#    #+#             */
/*   Updated: 2024/08/23 19:22:49 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void	print_numeric_error(t_shell *data, char *arg)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(": numeric argument required", 2);
	data->status = 2;
	free_all(data);
	exit(2);
}

static int	check_too_many_arguments(t_shell *data, t_cmd *cmd)
{
	if (cmd->n_args > 2)
	{
		if (isnum(cmd->arg[1]))
			ft_putendl_fd("minishell: exit: too many arguments", 2);
		else
			print_numeric_error(data, cmd->arg[1]);
		data->status = 1;
		return (1);
	}
	return (0);
}

static void	check_nums(t_shell *data, t_cmd *cmd)
{
	if (isnum(cmd->arg[1]) == 0)
		print_numeric_error(data, cmd->arg[1]);
}

void	ft_exit(t_shell *data, t_cmd *cmd)
{
	int		exit_code;
	long	num;

	exit_code = 1;
	ft_putstr_fd("exit\n", 2);
	if (check_too_many_arguments(data, cmd))
		return ;
	else if (cmd->n_args == 2)
	{
		check_nums(data, cmd);
		errno = 0;
		num = ft_atol(cmd->arg[1]);
		if (errno == ERANGE || num > LONG_MAX || num < LONG_MIN)
		{
			print_numeric_error(data, cmd->arg[1]);
			free_all(data);
			exit(255);
		}
		exit_code = (int)(num % 256);
	}
	free_all(data);
	exit(exit_code);
}
