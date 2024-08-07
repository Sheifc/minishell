#include "command.h"

Token	**tokenize_input(t_shell *data)
{
	data->tokens = NULL;
	if (data->prompt && ft_strlen(data->prompt) > 0)
	{
		// printf("\n**** Tokens: ****\n");
		data->tokens = tokenize(data);
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
		// printf("\n**** AST: ****\n");
		ast = build_ast(data->tokens, data->num_tokens, 0);
		// print_ast(ast);
	}
	return (ast);
}

bool	validate_and_free_tokens(t_shell *data)
{
	bool	is_valid;

	is_valid = false;
	if (data->tokens)
	{
		// printf("\n**** Validando: ****\n");
		is_valid = validate_ast(data->tokens, data->ast, &data->status);
		// printf("\nIs Valid: %d\n", is_valid);
		free_tokens(data->tokens, &data->num_tokens);
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
		// print_commands(cmd);
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
