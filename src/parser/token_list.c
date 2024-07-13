#include "minishell.h"

t_token	*ft_last(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	add_back(t_token **lst, t_token *new)
{
	t_token	*last;

	last = ft_last(*lst);
	if (!last)
		*lst = new;
	else
		last->next = new;
}

t_token	*create_token_node(int type, char *content)
{
	t_token	*node;

	node = (t_token *)malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	node->content = ft_strdup(content);
	node->type = type;
	node->next = NULL;
	return (node);
}

void	create_list(int type, t_token **token, char *content)
{
	t_token	*aux;

	if (!*token)
		*token = create_token_node(type, content);
	else
	{
		aux = create_token_node(type, content);
		add_back(token, aux);
	}
	free(content);
}
