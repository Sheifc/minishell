#include "ast.h"

// Function to create the corresponding redirect operator node
ASTNode	*build_redirect_node(Token *token, int level)
{
	if (token->type == T_OUTPUT)
		return (create_node(NODE_COMMAND, ">", level));
	if (token->type == T_OUTPUT_APPEND)
		return (create_node(NODE_COMMAND, ">>", level));
	if (token->type == T_INPUT)
		return (create_node(NODE_COMMAND, "<", level));
	if (token->type == T_HEREDOC)
		return (create_node(NODE_COMMAND, "<<", level));
	return (create_node(NODE_UNKNOWN, "-", level));
}

// Function to build the command node and its arguments
ASTNode	*build_command_node(Token **tokens, int num_tokens, int level)
{
	int		i;
	ASTNode	*root;
	ASTNode	*current;

	root = NULL;
	if (num_tokens > 0)
	{
		if (tokens[0]->type == T_ARG || tokens[0]->type == T_TEXT)
			return (create_node(NODE_ARGUMENT, tokens[0]->value, level + 1));
		root = create_node(NODE_COMMAND, tokens[0]->value, level);
		current = root;
		i = 1;
		while (i < num_tokens)
		{
			if (tokens[i]->type == T_ARG || tokens[i]->type == T_TEXT)
			{
				current->right = create_node(NODE_ARGUMENT, tokens[i]->value,
						level + 1);
				current = current->right;
			}
			i++;
		}
	}
	return (root);
}

// Function to handle redirects
ASTNode	*handle_operators(Token **tokens, int num_tokens, int level, int *pos)
{
	TokenType	op_type;
	ASTNode		*root;

	*pos = find_operator(tokens, num_tokens);
	if (*pos == ERROR)
	{
		printf(" ** Error parentesis: no se ha abierto un parentesis **\n");
		return (NULL);
	}
	if (*pos != NOT_FOUND)
	{
		op_type = tokens[*pos]->type;
		root = create_node(select_operator(op_type), tokens[*pos]->value,
				level);
		root->left = build_ast(tokens, *pos, level + 1);
		root->right = build_ast(tokens + *pos + 1, num_tokens - *pos - 1, level
				+ 1);
		return (root);
	}
	return (NULL);
}

// Function to handle parentheses
ASTNode	*handle_parentheses(Token **tokens, int num_tokens, int level)
{
	ASTNode	*root;
	int		close_pos;

	close_pos = find_matching_paren(tokens, 0, num_tokens);
	if (close_pos == NOT_FOUND)
	{
		printf(" ** Error parentesis: no se ha cerrado un parentesis **\n");
		return (NULL);
	}
	root = create_node(NODE_PARENTHESIS, "()", level);
	root->right = NULL;
	root->left = build_ast(tokens + 1, close_pos - 1, level + 1);
	return (root);
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
