/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:47:23 by sheferna          #+#    #+#             */
/*   Updated: 2024/08/27 18:47:24 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

bool	is_command_with_args(t_ast_node *node, int *status)
{
	t_ast_node	*child;

	if (node == NULL)
		return (false);
	if (node->type != NODE_COMMAND)
	{
		ft_error_ope(E_SYNTAX, node->value, "is not a command", status);
		return (false);
	}
	child = node->left;
	while (child != NULL)
	{
		if (child->type != NODE_ARGUMENT)
		{
			ft_error_ope(E_SYNTAX, node->value, "has no valid argument",
				status);
			return (false);
		}
		child = child->left;
	}
	return (true);
}

static bool	are_all_child_args(t_ast_node *child)
{
	while (child != NULL)
	{
		if (child->type != NODE_ARGUMENT)
			return (false);
		child = child->right;
	}
	return (true);
}

bool	is_command_with_args_mandatory(t_ast_node *node, int *status)
{
	if (node == NULL)
		return (false);
	if (node->type != NODE_COMMAND)
	{
		ft_error_ope(E_SYNTAX, node->value, "is not a command", status);
		return (false);
	}
	if (node->left == NULL)
	{
		ft_error_ope(E_SYNTAX, node->value, "requires mandatory argument",
			status);
		return (false);
	}
	if (!are_all_child_args(node->left))
	{
		ft_error_ope(E_SYNTAX, node->value, "has invalid argument", status);
		return (false);
	}
	return (true);
}

bool	is_binary_operator_valid(t_ast_node *node, int *status)
{
	if (node == NULL)
		return (false);
	if (node->left == NULL || node->right == NULL)
	{
		ft_error_syntax(E_SYNTAX, node->value, "syntax error near unexpected "
			"token", status);
		return (false);
	}
	return (is_ast_valid(node->left, status) && is_ast_valid(node->right,
			status));
}

bool	is_redirection_valid(t_ast_node *node, int *status)
{
	t_ast_node	*child;

	if (node == NULL)
		return (false);
	if (node->right == NULL)
	{
		ft_error_syntax(E_SYNTAX, "newline", "syntax error near unexpected "
			"token", status);
		return (false);
	}
	child = node->right;
	if (!child || (child->type != NODE_COMMAND))
	{
		ft_error_syntax(E_SYNTAX, "newline", "syntax error near unexpected "
			"token", status);
		return (false);
	}
	return (true);
}
