#include "ast.h"

// Function to create an AST node
ASTNode	*create_node(NodeType type, char *value, int level)
{
	ASTNode	*node;

	node = (ASTNode *)malloc(sizeof(ASTNode));
	node->level = level;
	node->type = type;
	node->value = strdup(value);
	node->left = NULL;
	node->right = NULL;
	return (node);
}

// Function to free the AST memory
void	free_ast(ASTNode *root)
{
	if (root == NULL)
		return ;
	free_ast(root->left);
	free_ast(root->right);
	free(root->value);
	free(root);
}

// Main function to build the AST
ASTNode	*build_ast(Token **tokens, int num_tokens, int level)
{
	int			op_pos;
	TokenType	op_type;
	ASTNode		*root;

	if (num_tokens <= 0 || tokens == NULL)
		return (NULL);
	op_pos = find_operator(tokens, num_tokens);
	if (op_pos != -1)
	{
		op_type = tokens[op_pos]->type;
		root = create_node(select_operator(op_type), tokens[op_pos]->value,
				level);
		root->left = build_ast(tokens, op_pos, level + 1);
		root->right = build_ast(tokens + op_pos + 1, num_tokens - op_pos - 1,
				level + 1);
		return (root);
	}
	if (tokens[0]->type == T_PAREN_OPEN)
		return (handle_parentheses(tokens, num_tokens, level));
	root = handle_redirection(tokens, num_tokens, level);
	if (root != NULL)
		return (root);
	return (build_command_node(tokens, num_tokens, level));
}
