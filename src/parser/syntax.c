#include "syntax.h"

bool	is_parenthesis_valid(ASTNode *node)
{
	if (node == NULL)
		return (false);
	if (node->left == NULL)
	{
		printf("\e[31m ** Error parentesis: (%d)%s[%d]: requiere agrupar algún "
			"elemento\e[0m\n", node->level, node->value, node->type);
		return (false);
	}
	return (is_ast_valid(node->left));
}

bool	is_ast_valid(ASTNode *root)
{
	if (root == NULL)
		return (true);
	else if (root->type == NODE_COMMAND)
		return (is_command_with_args(root));
	else if (root->type == NODE_AND || root->type == NODE_OR
		|| root->type == NODE_PIPE || root->type == NODE_SEMICOLON)
		return (is_binary_operator_valid(root));
	else if (root->type == NODE_INPUT || root->type == NODE_OUTPUT
		|| root->type == NODE_OUTPUT_APPEND || root->type == NODE_HEREDOC)
		return (is_redirection_valid(root));
	else if (root->type == NODE_PARENTHESIS)
		return (is_parenthesis_valid(root));
	else
	{
		printf("\e[31m ** Error nodo: (%d) %s[%d]:  tipo no soportado\e[0m\n",
			root->level, root->value, root->type);
		return (false);
	}
}

bool	validate_ast(Token **tokens, ASTNode *root)
{
	if (tokens != NULL && root == NULL)
		return (false);
	return (is_ast_valid(root));
}
