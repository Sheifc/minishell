/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:45:45 by sheferna          #+#    #+#             */
/*   Updated: 2024/08/27 18:45:46 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

// Function to create an AST node
t_ast_node	*create_node(t_node_type type, char *value, int level)
{
	t_ast_node	*node;

	node = (t_ast_node *)malloc(sizeof(t_ast_node));
	if (!node)
	{
		ft_error(E_MEMORY, NULL, NULL);
		return (NULL);
	}
	node->level = level;
	node->type = type;
	node->value = ft_strdup(value);
	node->left = NULL;
	node->right = NULL;
	return (node);
}

void	ft_free_str(char **str)
{
	if (*str != NULL)
		free(*str);
	*str = NULL;
}

// Function to free the AST memory
void	free_ast(t_ast_node **root)
{
	if ((*root) == NULL)
		return ;
	free((*root)->value);
	free_ast(&(*root)->left);
	free_ast(&(*root)->right);
	free(*root);
	*root = NULL;
}

// Main function to build the AST
t_ast_node	*build_ast(t_token **tokens, int num_tokens, int level)
{
	int			result;
	t_ast_node	*root;

	result = NOT_FOUND;
	if (num_tokens <= 0 || tokens == NULL)
		return (NULL);
	root = handle_operators(tokens, num_tokens, level, &result);
	if (result == ERROR)
		return (NULL);
	if (root != NULL)
		return (root);
	if (tokens[0]->type == T_PAREN_OPEN || tokens[0]->type == T_PAREN_CLOSE)
		return (handle_parentheses(tokens, num_tokens, level));
	root = handle_redirection(tokens, num_tokens, level);
	if (root != NULL)
		return (root);
	return (build_command_node(tokens, num_tokens, level));
}
