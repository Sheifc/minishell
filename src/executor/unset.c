/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 19:24:45 by sheferna          #+#    #+#             */
/*   Updated: 2024/08/23 19:24:47 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_shell *data)
{
	char	*str;
	int		i;

	i = 1;
	while (data->cmd->arg[i])
	{
		str = data->cmd->arg[i];
		pop(&data->env, str);
		pop(&data->export, str);
		i++;
	}
	data->status = 0;
}
