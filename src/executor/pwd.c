/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 19:24:04 by sheferna          #+#    #+#             */
/*   Updated: 2024/08/23 19:24:05 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_current_directory(t_shell *data)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		ft_putendl_fd("minishell: getcwd: "
			"No such file or directory", 2);
		data->status = 1;
		return (NULL);
	}
	return (path);
}

void	ft_pwd(t_shell *data)
{
	char	*path;

	path = get_current_directory(data);
	if (!path)
	{
		data->status = 1;
		return ;
	}
	printf("%s\n", path);
	free(path);
	data->status = 0;
}
