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
