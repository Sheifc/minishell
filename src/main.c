#include "minishell.h"

int	handle_empty_or_whitespace_commands(char **prompt)
{
	if (!ft_strlen(*prompt) || only_spaces(*prompt) == 1)
	{
		free(*prompt);
		return (0);
	}
	return (1);
}

static void	minishell(t_shell *data)
{
	if (data->cmd != NULL)
	{
		executor(data);
		free_commands(&data->cmd);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell		data;
	int			num_tokens;
	init(&data, envp);
	while (1)
	{
		data.prompt = readline("minishell$ ");
		if (!data.prompt)
			break ;
		add_history(data.prompt);
		if (handle_empty_or_whitespace_commands(&data.prompt))
		{
			data.tokens = tokenize_input(data.prompt, &num_tokens);
			data.ast = create_ast(data.tokens, num_tokens);
			data.cmd = generate_commands(data.ast,
					validate_and_free_tokens(data.tokens, &num_tokens, data.ast),
					(Fds){-1, -1});
			minishell(&data);
			free(data.prompt);
			data.cmd_count = 0;
			data.prompt = NULL;
		}
	}
	free_all(&data);
	return ((void)argc, (void)argv, data.status);
}
