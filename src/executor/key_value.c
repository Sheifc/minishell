/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 19:23:33 by sheferna          #+#    #+#             */
/*   Updated: 2024/08/23 19:23:35 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_key_value(char *str, char **key, char **value)
{
	char	*equal;

	if (str == NULL || key == NULL || value == NULL)
		return ;
	*key = ft_substr(str, 0, ft_strchr(str, '=') - str);
	equal = ft_strchr(str, '=');
	if (equal)
		*value = ft_strdup(equal + 1);
	else
		*value = NULL;
}

char	*get_value(t_env *env, const char *key)
{
	t_env	*current;

	if (env == NULL || key == NULL)
		return (NULL);
	current = env;
	while (current != NULL)
	{
		if (!ft_strncmp(current->key, key, ft_strlen(key) + 1))
			return (current->value);
		current = current->next;
	}
	return (NULL);
}
