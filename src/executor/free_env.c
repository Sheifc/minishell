/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 19:23:19 by sheferna          #+#    #+#             */
/*   Updated: 2024/08/23 19:23:20 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env_list(t_env *head)
{
	t_env	*temp;

	while (head != NULL)
	{
		temp = head;
		head = head->next;
		if (temp->key)
			free(temp->key);
		if (temp->value)
			free(temp->value);
		free(temp);
	}
}

void	free_env_node(t_env **node)
{
	if (!node)
		return ;
	if ((*node)->key)
		free((*node)->key);
	if ((*node)->value)
		free((*node)->value);
	free(*node);
	*node = NULL;
}
