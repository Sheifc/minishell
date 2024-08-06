#include "syntax.h"

bool	is_parenthesis_valid(ASTNode *node, int *status)
{
	if (node == NULL)
		return (false);
	if (node->left == NULL)
	{
		ft_error_ope(E_SYNTAX, node->value, "requiere agrupar algún elemento",
			status);
		return (false);
	}
	return (is_ast_valid(node->left, status));
}

bool	is_ast_valid(ASTNode *root, int *status)
{
	if (root == NULL)
		return (true);
	else if (root->type == NODE_COMMAND)
		return (is_command_with_args(root, status));
	else if (root->type == NODE_AND || root->type == NODE_OR
		|| root->type == NODE_PIPE)
		return (is_binary_operator_valid(root, status));
	else if (root->type == NODE_SEMICOLON)
		return (is_ast_valid(root->left, status) && is_ast_valid(root->right,
				status));
	else if (root->type == NODE_PARENTHESIS)
		return (is_parenthesis_valid(root, status));
	else if (root->type == NODE_INPUT || root->type == NODE_HEREDOC
		|| root->type == NODE_OUTPUT || root->type == NODE_OUTPUT_APPEND)
		return (is_redirection_valid(root, status));
	else
	{
		ft_error_ope(E_SYNTAX, root->value, "tipo no soportado", status);
		return (false);
	}
}

bool	validate_ast(Token **tokens, ASTNode *root, int *status)
{
	if (tokens != NULL && root == NULL)
		return (false);
	return (is_ast_valid(root, status));
}
