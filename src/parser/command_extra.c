#include "command.h"

Token	**tokenize_input(const char *input, int *num_tokens)
{
	Token	**tokens;

	tokens = NULL;
	if (input && ft_strlen(input) > 0)
	{
		tokens = tokenize(input, num_tokens);
		// printf("\n**** Tokens: ****\n");
		// print_tokens(tokens, *num_tokens);
		verify_tokens(tokens, num_tokens);
		if (verify_tokens(tokens, num_tokens) != 0)
			free_tokens(tokens, num_tokens);
	}
	return (tokens);
}

ASTNode	*create_ast(Token **tokens, int num_tokens)
{
	ASTNode	*ast;

	ast = NULL;
	if (tokens)
	{
		ast = build_ast(tokens, num_tokens, 0);
		// printf("\n**** AST: ****\n");
		// print_ast(ast);
	}
	return (ast);
}

bool	validate_and_free_tokens(Token **tokens, int *num_tokens, ASTNode *ast)
{
	bool	is_valid;

	is_valid = true;
	if (tokens)
	{
		is_valid = validate_ast(tokens, ast);
		free_tokens(tokens, num_tokens);
	}
	return (is_valid);
}

t_cmd	*generate_commands(ASTNode *ast, bool is_valid, Fds fds)
{
	OperatorStack	*ope_stack;
	PipeStack		*pipe_stack;
	t_cmd			*cmd;

	ope_stack = NULL;
	pipe_stack = NULL;
	cmd = NULL;
	if (ast)
	{
		// printf("\n**** Generating Commands: ****\n");
		if (is_valid)
			cmd = traverse_ast(ast, fds, &ope_stack, &pipe_stack);
		postprocess_cmds(cmd);
		free_ast(&ast);
		free(pipe_stack);
	}
	return (cmd);
}

void	print_commands(t_cmd *cmd)
{
	t_cmd	*current;

	current = NULL;
	if (cmd)
	{
		printf("\n**** List of Commands: ****\n");
		current = cmd;
		while (current)
		{
			print_command(current);
			current = current->next;
		}
	}
}
