#include "ast.h"

// // Function to create the corresponding redirect operator node
// ASTNode	*build_redirect_node(Token *token, int level)
// {
// 	if (token->type == T_OUTPUT)
// 		return (create_node(NODE_OUTPUT, ">", level));
// 	if (token->type == T_OUTPUT_APPEND)
// 		return (create_node(NODE_OUTPUT_APPEND, ">>", level));
// 	if (token->type == T_INPUT)
// 		return (create_node(NODE_INPUT, "<", level));
// 	if (token->type == T_HEREDOC)
// 		return (create_node(NODE_HEREDOC, "<<", level));
// 	return (create_node(NODE_UNKNOWN, "-", level));
// }

// Function to build the command node and its arguments
ASTNode	*build_command_node(Token **tokens, int num_tokens, int level)
{
	int		i;
	ASTNode	*root;
	ASTNode	*current;

	root = NULL;
	if (num_tokens > 0)
	{
		i = -1;
		while (++i < num_tokens && tokens[i]->type == T_QUOTE)
			;
		root = create_node(NODE_COMMAND, tokens[i]->value, level);
		current = root;
		while (++i < num_tokens)
		{
			if (tokens[i]->type == T_ARG || tokens[i]->type == T_TEXT
				|| tokens[i]->type == T_WILDCARD)
			{
				current->left = create_node(NODE_ARGUMENT, tokens[i]->value,
						level + 1);
				current = current->left;
			}
		}
	}
	return (root);
}

ASTNode	*build_redirect_node(Token **tokens, char *name, int num_tokens,
		int level)
{
	ASTNode	*root;

	root = NULL;
	if (num_tokens > 0)
	{
		root = create_node(NODE_COMMAND, name, level);
		root->left = create_node(NODE_ARGUMENT, tokens[0]->value, level + 1);
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
		printf("\e[31m ** Error parentesis: no se ha abierto **\e[0m\n");
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
		printf("\e[31m ** Error parentesis: no se ha cerrado **\e[0m\n");
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
	int i = -1;
	if (num_tokens > 0)
	{
		while (++i < num_tokens && tokens[i]->type == T_QUOTE)
			;
		if (tokens[i]->type == T_REDIRECT_ARG)
		{
			if ((tokens - 1)[0]->type == T_OUTPUT)
				return (build_redirect_node(&tokens[i], "save_outfile", num_tokens,
						level));
			if ((tokens - 1)[0]->type == T_OUTPUT_APPEND)
				return (build_redirect_node(&tokens[i], "save_append", num_tokens,
						level));
			if ((tokens - 1)[0]->type == T_INPUT)
				return (build_redirect_node(&tokens[i], "read_infile", num_tokens,
						level));
			if ((tokens - 1)[0]->type == T_HEREDOC)
				return (build_redirect_node(&tokens[i], "heredoc", num_tokens,
						level));
			return (build_redirect_node(&tokens[i], "cat", num_tokens, level));
		}
	}
	return (NULL);
}
