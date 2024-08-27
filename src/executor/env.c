/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 19:21:16 by sheferna          #+#    #+#             */
/*   Updated: 2024/08/23 19:21:18 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_env_list(t_env **head, char **envp, int *i)
{
	char	*key;
	char	*value;

	while (envp[++(*i)] != NULL)
	{
		get_key_value(envp[*i], &key, &value);
		add(head, key, value);
	}
}

void	init_env(t_shell *data, char **envp)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	fill_env_list(&(data->env), envp, &i);
	fill_env_list(&(data->export), envp, &j);
}

void	print_env(t_env *env)
{
	t_env	*current;

	current = env;
	while (current != NULL)
	{
		if (current->value && *(current->value) != '\0')
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
}

void	ft_env(t_shell *data, t_env *env)
{
	if (!data->cmd->arg[1] || ft_strncmp(data->cmd->arg[1], "env\0", 4) == 0)
	{
		print_list(env);
		data->status = 0;
		return ;
	}
	handle_env_error(data->cmd->arg[1], data);
	return ;
}
