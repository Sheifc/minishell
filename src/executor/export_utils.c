/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 19:22:55 by sheferna          #+#    #+#             */
/*   Updated: 2024/08/23 19:22:56 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export(t_shell *data)
{
	t_env	*env;

	env = data->export;
	while (env)
	{
		if (env->value && ft_strlen(env->value) == 0)
			printf("declare -x %s", env->key);
		else
			printf("declare -x %s=", env->key);
		printf("%s\n", env->value);
		env = env->next;
	}
}

int	is_valid(t_shell *data)
{
	char	**str;
	int		i;
	int		j;

	i = 1;
	str = data->cmd->arg;
	while (str[i])
	{
		j = 0;
		while (str[i][j] && str[i][j] != '=')
		{
			if ((ft_isdigit(str[i][0]) || !ft_isalnum(str[i][j]))
				&& str[i][j] != '_')
			{
				printf("export: %s: not a valid identifier\n", str[i]);
				data->status = 1;
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

t_env	*new_node(int i)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->value = NULL;
	new->key = ft_calloc(sizeof(char), i + 1);
	new->next = NULL;
	return (new);
}

void	addback_node(t_env **export, t_env *aux)
{
	t_env	*actual;

	if (!*export)
		*export = aux;
	else
	{
		actual = *export;
		while (actual->next != NULL)
			actual = actual->next;
		actual->next = aux;
	}
}

void	ft_swap(char **a, char **b)
{
	char	*aux;

	aux = *a;
	*a = *b;
	*b = aux;
}
