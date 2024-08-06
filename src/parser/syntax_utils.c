#include "syntax.h"

bool	is_command_with_args(ASTNode *node, int *status)
{
	ASTNode	*child;

	if (node == NULL)
		return (false);
	if (node->type != NODE_COMMAND)
	{
		ft_error_ope(E_SYNTAX, node->value, "no es un comando", status);
		return (false);
	}
	child = node->left;
	while (child != NULL)
	{
		if (child->type != NODE_ARGUMENT)
		{
			ft_error_ope(E_SYNTAX, node->value, "no posee argumento valido",
				status);
			return (false);
		}
		child = child->left;
	}
	return (true);
}

static bool	are_all_child_args(ASTNode *child)
{
	while (child != NULL)
	{
		if (child->type != NODE_ARGUMENT)
			return (false);
		child = child->right;
	}
	return (true);
}

bool	is_command_with_args_mandatory(ASTNode *node, int *status)
{
	if (node == NULL)
		return (false);
	if (node->type != NODE_COMMAND)
	{
		ft_error_ope(E_SYNTAX, node->value, "no es un comando", status);
		return (false);
	}
	if (node->left == NULL)
	{
		ft_error_ope(E_SYNTAX, node->value, "requiere argumento obligatorio",
			status);
		return (false);
	}
	if (!are_all_child_args(node->left))
	{
		ft_error_ope(E_SYNTAX, node->value, "posee argumento invalido", status);
		return (false);
	}
	return (true);
}

bool	is_binary_operator_valid(ASTNode *node, int *status)
{
	if (node == NULL)
		return (false);
	if (node->left == NULL || node->right == NULL)
	{
		ft_error_ope(E_SYNTAX, node->value, "requiere dos operandos validos",
			status);
		return (false);
	}
	return (is_ast_valid(node->left, status) && is_ast_valid(node->right,
			status));
}

bool	is_redirection_valid(ASTNode *node, int *status)
{
	ASTNode	*child;

	if (node == NULL)
		return (false);
	if (node->left == NULL || node->right == NULL)
	{
		ft_error_ope(E_REDIRECT, node->value, "requiere dos operandos validos",
			status);
		return (false);
	}
	child = node->right;
	if (!child || (child->type != NODE_COMMAND))
	{
		ft_error_ope(E_REDIRECT, node->value, "no posee argumento valido",
			status);
		return (false);
	}
	return (true);
}
