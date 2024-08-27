/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 19:25:05 by sheferna          #+#    #+#             */
/*   Updated: 2024/08/27 18:43:02 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_sig;

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
		g_sig = 1;
		init_signals();
		executor(data);
		free_commands(&data->cmd);
	}
}

void	load_data(t_shell *data)
{
	bool	ast_status;

	ast_status = false;
	data->tokens = tokenize_input(data);
	data->ast = create_ast(data);
	ast_status = validate_and_free_tokens(data);
	data->cmd = generate_commands(data, ast_status, (t_fds){-1, -1});
	free(data->tokens);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	data;

	init(&data, envp);
	while (1)
	{
		data.prompt = readline("minishell$ ");
		if (!data.prompt)
			signal_d(&data);
		add_history(data.prompt);
		if (handle_empty_or_whitespace_commands(&data.prompt))
		{
			load_data(&data);
			minishell(&data);
			free(data.prompt);
			data.cmd_count = 0;
			data.prompt = NULL;
			g_sig = 0;
			init_signals();
		}
	}
	free_all(&data);
	return ((void)argc, (void)argv, data.status);
}
