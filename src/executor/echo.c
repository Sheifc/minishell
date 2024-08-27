/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 19:21:02 by sheferna          #+#    #+#             */
/*   Updated: 2024/08/23 19:21:04 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_cmd(t_cmd *cmd, int i, int newline)
{
	while (cmd->arg[i])
	{
		printf("%s", cmd->arg[i]);
		if (cmd->arg[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
}

void	ft_echo(t_shell *data, t_cmd *cmd)
{
	int	i;
	int	j;
	int	newline;

	i = 1;
	newline = 1;
	while (cmd->arg[i] && ft_strncmp(cmd->arg[i], "-n", 2) == 0)
	{
		j = 1;
		while (cmd->arg[i][j] == 'n')
			j++;
		if (cmd->arg[i][j] != '\0')
			break ;
		newline = 0;
		i++;
	}
	print_cmd(cmd, i, newline);
	data->status = 0;
}
