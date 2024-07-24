#include "syntax.h"

bool	is_command_with_args(ASTNode *node)
{
	ASTNode	*child;

	if (node == NULL)
		return (false);
	if (node->type != NODE_COMMAND)
	{
		printf("\e[31m ** Error comando: (%d) %s[%d]: no es un comando\e[0m\n",
			node->level, node->value, node->type);
		return (false);
	}
	child = node->left;
	while (child != NULL)
	{
		if (child->type != NODE_ARGUMENT)
		{
			printf("\e[31m ** Error comando: (%d) %s[%d]: no posee argumento "
				"valido\e[0m\n", node->level, node->value, node->type);
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

bool	is_command_with_args_mandatory(ASTNode *node)
{
	if (node == NULL)
		return (false);
	if (node->type != NODE_COMMAND)
	{
		printf("\e[31m ** Error comando: (%d) %s[%d]: no es un comando\e[0m\n",
			node->level, node->value, node->type);
		return (false);
	}
	if (node->left == NULL)
	{
		printf("\e[31m ** Error comando: (%d) %s[%d]: requiere argumento "
			"obligatorio\e[0m\n", node->level, node->value, node->type);
		return (false);
	}
	if (!are_all_child_args(node->left))
	{
		printf("\e[31m ** Error comando: (%d) %s[%d]: posee argumento "
			"invalido\e[0m\n", node->level, node->value, node->type);
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
		printf("\e[31m ** Error operador: (%d) %s[%d]: requiere dos operandos "
			"validos\e[0m\n", node->level, node->value, node->type);
		return (false);
	}
	return (is_ast_valid(node->left) && is_ast_valid(node->right));
}

bool	is_redirection_valid(ASTNode *node)
{
	ASTNode	*child;

	if (node == NULL)
		return (false);
	if (node->left == NULL || node->right == NULL)
	{
		printf("\e[31m ** Error redireccion: (%d) %s[%d]: requiere dos "
			"operandos validos\e[0m\n", node->level, node->value, node->type);
		return (false);
	}
	child = node->right;
	if (!child || (child->type != NODE_INPUT && child->type != NODE_HEREDOC
			&& child->type != NODE_OUTPUT && child->type != NODE_OUTPUT_APPEND))
	{
		printf("\e[31m ** Error comando: (%d) %s[%d]: no posee argumento "
			"valido\e[0m\n", node->level, node->value, node->type);
		return (false);
	}
	return (true);
}
