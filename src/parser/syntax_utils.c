#include "syntax.h"

bool	is_command_with_args(ASTNode *node)
{
	ASTNode	*child;

	if (node == NULL)
		return (false);
	if (node->type != NODE_COMMAND)
	{
		printf(" ** Error comando: (%d) %s[%d]: no es un comando\n",
			node->level, node->value, node->type);
		return (false);
	}
	child = node->left;
	while (child != NULL)
	{
		if (child->type != NODE_ARGUMENT)
		{
			printf(" ** Error comando: (%d) %s[%d]: no posee argumento "
				"valido\n", node->level, node->value, node->type);
			return (false);
		}
		child = child->right;
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

bool	is_command_with_args_mandatory(ASTNode *node)
{
	if (node == NULL)
		return (false);
	if (node->type != NODE_COMMAND)
	{
		printf(" ** Error comando: (%d) %s[%d]: no es un comando\n",
			node->level, node->value, node->type);
		return (false);
	}
	if (node->left == NULL)
	{
		printf(" ** Error comando: (%d) %s[%d]: requiere argumento "
			"obligatorio\n", node->level, node->value, node->type);
		return (false);
	}
	if (!are_all_child_args(node->left))
	{
		printf(" ** Error comando: (%d) %s[%d]: posee argumento "
			"invalido\n", node->level, node->value, node->type);
		return (false);
	}
	return (true);
}

bool	is_binary_operator_valid(ASTNode *node)
{
	if (node == NULL)
		return (false);
	if (node->left == NULL || node->right == NULL)
	{
		printf(" ** Error operador: (%d) %s[%d]: requiere dos operandos "
			"validos\n", node->level, node->value, node->type);
		return (false);
	}
	return (is_ast_valid(node->left) && is_ast_valid(node->right));
}

bool	is_redirection_valid(ASTNode *node)
{
	if (node == NULL)
		return (false);
	if (node->left == NULL || node->right == NULL)
	{
		printf(" ** Error redireccion: (%d) %s[%d]: requiere dos operandos "
			"validos\n", node->level, node->value, node->type);
		return (false);
	}
	if (!is_command_with_args(node->left))
	{
		printf(" ** Error redireccion: (%d) %s[%d]: %s no es un comando\n",
			node->level, node->value, node->type, node->left->value);
		return (false);
	}
	if (!is_command_with_args_mandatory(node->right))
	{
		printf(" ** Error redireccion: (%d) %s[%d]: requiere argumento "
			"obligatorio\n", node->level, node->value, node->type);
		return (false);
	}
	return (true);
}
