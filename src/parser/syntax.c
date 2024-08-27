/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:47:28 by sheferna          #+#    #+#             */
/*   Updated: 2024/08/27 18:47:29 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

bool	is_parenthesis_valid(t_ast_node *node, int *status)
{
	if (node == NULL)
		return (false);
	if (node->left == NULL)
	{
		ft_error_ope(E_SYNTAX, node->value, "requires grouping some element",
			status);
		return (false);
	}
	return (is_ast_valid(node->left, status));
}

bool	is_ast_valid(t_ast_node *root, int *status)
{
	if (root == NULL)
		return (true);
	else if (root->type == NODE_COMMAND)
		return (is_command_with_args(root, status));
	else if (root->type == NODE_AND || root->type == NODE_OR
		|| root->type == NODE_PIPE)
		return (is_binary_operator_valid(root, status));
	else if (root->type == NODE_PARENTHESIS)
		return (is_parenthesis_valid(root, status));
	else if (root->type == NODE_INPUT || root->type == NODE_HEREDOC
		|| root->type == NODE_OUTPUT || root->type == NODE_OUTPUT_APPEND)
		return (is_redirection_valid(root, status));
	else
	{
		ft_error_syntax(E_SYNTAX, root->value,
			"syntax error near unexpected token", status);
		return (false);
	}
}

bool	validate_ast(t_token **tokens, t_ast_node *root, int *status)
{
	if (tokens != NULL && root == NULL)
		return (false);
	return (is_ast_valid(root, status));
}
