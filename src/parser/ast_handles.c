#include "ast.h"

// Function to find the corresponding closing parenthesis
static int	find_matching_paren(Token **tokens, int start, int num_tokens)
{
	int	depth;
	int	i;

	depth = 1;
	i = start + 1;
	while (i < num_tokens)
	{
		if (tokens[i]->type == T_PAREN_OPEN)
			depth++;
		else if (tokens[i]->type == T_PAREN_CLOSE)
		{
			depth--;
			if (depth == 0)
				return (i);
		}
		i++;
	}
	return (-1);
}

// Function to create the corresponding redirect operator node
ASTNode	*build_redirect_node(Token *token, int level)
{
	if (token->type == T_OUTPUT)
		return (create_node(NODE_COMMAND, "output", level));
	if (token->type == T_OUTPUT_APPEND)
		return (create_node(NODE_COMMAND, "output_append", level));
	if (token->type == T_INPUT)
		return (create_node(NODE_COMMAND, "input", level));
	if (token->type == T_HEREDOC)
		return (create_node(NODE_COMMAND, "heredoc", level));
	return (create_node(NODE_UNKNOWN, "-", level));
}

// Function to build the command node and its arguments
ASTNode	*build_command_node(Token **tokens, int num_tokens, int level)
{
	int		i;
	ASTNode	*root;
	ASTNode	*current;

	if (tokens[0]->type == T_ARG || tokens[0]->type == T_TEXT)
		return (create_node(NODE_ARGUMENT, tokens[0]->value, level + 1));
	root = create_node(NODE_COMMAND, tokens[0]->value, level);
	current = root;
	i = 1;
	while (i < num_tokens)
	{
		if (tokens[i]->type == T_ARG || tokens[i]->type == T_TEXT)
		{
			current->right = create_node(NODE_ARGUMENT, tokens[i]->value, level
					+ 1);
			current = current->right;
		}
		i++;
	}
	return (root);
}

// Function to handle parentheses
ASTNode	*handle_parentheses(Token **tokens, int num_tokens, int level)
{
	int	close_pos;

	close_pos = find_matching_paren(tokens, 0, num_tokens);
	if (close_pos == -1)
		return (NULL);
	return (build_ast(tokens + 1, close_pos - 1, level));
}

// Function to handle redirects
ASTNode	*handle_redirection(Token **tokens, int num_tokens, int level)
{
	ASTNode	*root;
	ASTNode	*redirect;
	int		i;

	i = -1;
	while (++i < num_tokens)
	{
		if (tokens[i]->type == T_OUTPUT || tokens[i]->type == T_OUTPUT_APPEND
			|| tokens[i]->type == T_INPUT || tokens[i]->type == T_HEREDOC)
		{
			root = create_node(select_redirection(tokens[i]->type),
					tokens[i]->value, level);
			redirect = build_redirect_node(tokens[i], level + 1);
			root->left = build_ast(tokens, i, level + 1);
			root->right = redirect;
			redirect->left = build_ast(tokens + i + 1, num_tokens - i - 1, level
					+ 1);
			return (root);
		}
	}
	return (NULL);
}
