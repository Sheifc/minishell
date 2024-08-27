/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 19:23:01 by sheferna          #+#    #+#             */
/*   Updated: 2024/08/23 19:23:02 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	pop_node_export(t_env **head, char *str)
{
	t_env	*previous;
	t_env	*current;

	if (*head == NULL)
		return ;
	current = *head;
	if (ft_strncmp(current->key, str, ft_strlen(str)+1) == 0)
	{
		*head = (*head)->next;
		free_env_node(&current);
		return ;
	}
	previous = *head;
	current = (*head)->next;
	while (current && ft_strncmp(current->key, str, ft_strlen(str)+1))
	{
		previous = current;
		current = current->next;
	}
	if (current)
	{
		previous->next = current->next;
		free_env_node(&current);
	}
}

static void	sort_export(t_shell *data)
{
	t_env	*one;
	t_env	*other;

	one = data->export;
	while (one && one->next)
	{
		other = data->export;
		while (other->next)
		{
			if (ft_strncmp(other->key, other->next->key,
					ft_strlen(other->key)) > 0)
			{
				ft_swap(&other->key, &other->next->key);
				ft_swap(&other->value, &other->next->value);
			}
			other = other->next;
		}
		one = one->next;
	}
}

static void	add_node_export(int i, t_cmd *cmd, t_env **env)
{
	char	**str;
	t_env	*aux;
	int		j;

	aux = *env;
	str = cmd->arg;
	while (str[++i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] == '=')
				break ;
			j++;
		}
		aux = new_node(j);
		ft_strlcpy(aux->key, str[i], ++j);
		if (str[i][j - 1] != '=')
			aux->value = ft_strdup("");
		else
			aux->value = ft_strdup(&str[i][j]);
		pop_node_export(env, aux->key);
		addback_node(env, aux);
		aux->next = NULL;
	}
}

void	ft_export(t_shell *data, t_cmd *cmd)
{
	int	i;

	i = -1;
	if (cmd->n_args > 1)
	{
		if (!is_valid(data))
			return ;
		add_node_export(0, cmd, &data->export);
		while (cmd->arg[++i])
		{
			if (ft_strchr(cmd->arg[i], '='))
				add_node_export(0, cmd, &data->env);
		}
	}
	else
	{
		sort_export(data);
		print_export(data);
	}
	data->status = 0;
}
