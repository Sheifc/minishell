#include "command.h"
#include "minishell.h"

t_token	**tokenize_input(t_shell *data)
{
	data->tokens = NULL;
	if (data->prompt && ft_strlen(data->prompt) > 0)
	{
		if (!ft_strlen(data->prompt) || only_wildcard(data->prompt) == 1)
		{
			ft_error(E_COMMAND, "command not found: No such file or directory",
				&data->status);
			return (data->tokens);
		}
		// printf("\n**** Tokens: ****\n");
		data->tokens = tokenize(data);
		// print_tokens(data->tokens, data->num_tokens);
		if (verify_tokens(data) != 0)
			free_tokens(&data->tokens, &data->num_tokens);
	}
	return (data->tokens);
}

t_ast_node	*create_ast(t_shell *data)
{
	data->ast = NULL;
	if (data->tokens)
	{
		// printf("\n**** AST: ****\n");
		data->ast = build_ast(data->tokens, data->num_tokens, 0);
		// print_ast(data->ast);
	}
	return (data->ast);
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
	}
	free_tokens(&data->tokens, &data->num_tokens);
	return (is_valid);
}

t_cmd	*generate_commands(t_shell *data, bool is_valid, t_fds fds)
{
	t_operator_stack	*ope_stack;
	t_pipe_stack		*pipe_stack;
	t_cmd_arg			arg;

	data->cmd = NULL;
	ope_stack = NULL;
	pipe_stack = NULL;
	if (data->ast && is_valid)
	{
		arg.node = data->ast;
		arg.fds = fds;
		arg.ope_stack = &ope_stack;
		arg.pipe_stack = &pipe_stack;
		arg.open_parenthesis = false;
		data->cmd = traverse_ast(&arg, data);
		postprocess_cmds(data->cmd);
		if (data->cmd == NULL || data->cmd->name == NULL)
			data->cmd = NULL;
		// print_commands(data->cmd);
	}
	free_ast(&data->ast);
	if (pipe_stack != NULL)
		free(pipe_stack);
	if (ope_stack != NULL)
		free(ope_stack);
	return (data->cmd);
}

void	print_commands(t_cmd *cmd)
{
	t_cmd	*current;

	current = NULL;
	if (cmd && cmd->name)
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
