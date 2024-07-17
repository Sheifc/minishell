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
	if (root->value)
		free(root->value);
	free(root);
}

// Main function to build the AST
ASTNode	*build_ast(Token **tokens, int num_tokens, int level)
{
	int		result;
	ASTNode	*root;

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
