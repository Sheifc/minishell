#include "command.h"

Token	**tokenize_input(t_shell *data)
{
	data->tokens = NULL;
	if (data->prompt && ft_strlen(data->prompt) > 0)
	{
		data->tokens = tokenize(data);
		// printf("\n**** Tokens: ****\n");
		// print_tokens(data->tokens, data->num_tokens);
		if (verify_tokens(data) != 0)
			free_tokens(data->tokens, &data->num_tokens);
	}
	return (data->tokens);
}

ASTNode	*create_ast(t_shell *data)
{
	ASTNode	*ast;

	ast = NULL;
	if (data->tokens)
	{
		ast = build_ast(data->tokens, data->num_tokens, 0);
		// printf("\n**** AST: ****\n");
		// print_ast(ast);
	}
	return (ast);
}

bool	validate_and_free_tokens(Token **tokens, int *num_tokens, ASTNode *ast)
{
	bool	is_valid;

	is_valid = false;
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
		if (is_valid)
			cmd = traverse_ast(ast, fds, &ope_stack, &pipe_stack);
		postprocess_cmds(cmd);
		free_ast(&ast);
		free(pipe_stack);
		// printf("\n**** Generating Commands: ****\n");
		// print_commands(cmd);
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
