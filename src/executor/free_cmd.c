/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 19:23:13 by sheferna          #+#    #+#             */
/*   Updated: 2024/08/23 19:23:15 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_arg(char ***matrix)
{
	int	i;

	i = 0;
	if (!matrix || !*matrix || !*matrix[i])
		return ;
	while ((*matrix)[i])
	{
		free((*matrix)[i]);
		(*matrix)[i] = NULL;
		i++;
	}
	free(*matrix);
	*matrix = NULL;
}

void	free_cmd(t_cmd **cmd)
{
	t_cmd	*aux;

	if (!cmd)
		return ;
	while (*cmd)
	{
		aux = (*cmd)->next;
		if ((*cmd)->fdin > 2)
			close((*cmd)->fdin);
		if ((*cmd)->fdout > 2)
			close((*cmd)->fdout);
		free_arg(&((*cmd)->arg));
		free(*cmd);
		*cmd = aux;
	}
}

void	free_cmd_list(t_cmd **cmd_list)
{
	if (!cmd_list || !*cmd_list)
		return ;
	free_cmd(cmd_list);
	*cmd_list = NULL;
}
