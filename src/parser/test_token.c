/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 10:31:45 by svilla-d          #+#    #+#             */
/*   Updated: 2024/09/01 10:31:46 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

typedef struct s_test_token
{
	t_token_type	type;
	char			value[100];
}					t_test_token;

typedef struct s_test_case {
	const char		*input;
	const t_token	tokens[100];
	int				num_tokens;
}					t_test_case;

t_token	**tokenize_and_count(t_shell *data)
{
	data->tokens = tokenize(data);
	printf("Input: %s\n", data->prompt);
	return (data->tokens);
}

bool	compare_tokens(t_shell *d, const t_test_case *c)
{
	bool	error;
	int		i;

	error = false;
	if (d->num_tokens != c->num_tokens)
	{
		error = true;
		printf("\e[31m -> #tokens: %d,%d\n\e[0m", d->num_tokens, c->num_tokens);
	}
	printf("#\tResult\t\t\tExpected\n");
	i = -1;
	while (++i < d->num_tokens)
	{
		printf("%d\t[%d] %10s\t", i, d->tokens[i]->type, d->tokens[i]->value);
		if (i < c->num_tokens)
			printf("\t[%d] %10s", c->tokens[i].type, c->tokens[i].value);
		if (d->tokens[i]->type != c->tokens[i].type
			|| ft_strcmp(d->tokens[i]->value, c->tokens[i].value) != 0)
		{
			error = true;
			printf("\e[31m -> failed\e[0m");
		}
		printf("\n");
	}
	return (error);
}

void	free_tokens_and_print_result(t_shell *data, bool error)
{
	if (!error)
		printf("\e[32mTest case: ok\n\e[0m");
	else
		printf("\e[31mTest case: error\n\e[0m");
	printf("\n");
	free_tokens(&data->tokens, &data->num_tokens);
}

int	run_test_case(const t_test_case *c)
{
	t_shell	data;
	bool	error;

	data.prompt = (char *)c->input;
	data.tokens = tokenize_and_count(&data);
	if (data.tokens == NULL)
		return (1);
	error = compare_tokens(&data, c);
	free_tokens_and_print_result(&data, error);
	if (error)
		return (1);
	return (0);
}

int	main(void)
{
	int					i;
	int					errors;
	int					n;
	const t_test_case	cases[] = {
	{"ls -la", {{T_COMMAND, "ls", 1}, {T_ARG, "-la", 1}}, 2},
	{"ls | (pwd && cd '/home|' )", {{T_COMMAND, "ls", 1}, {T_PIPE, "|", 1},
	{T_PAREN_OPEN, "(", 1}, {T_COMMAND, "pwd", 1}, {T_AND, "&&", 1},
	{T_COMMAND, "cd", 1}, {T_ARG, "'/home|'", 1}, {T_PAREN_CLOSE, ")", 1}}, 8},
	{"ls -l -a file*.txt", {{T_COMMAND, "ls", 1}, {T_ARG, "-l", 1},
	{T_ARG, "-a", 1}, {T_WILDCARD, "file*.txt", 1}}, 4}
	};

	errors = 0;
	i = -1;
	n = sizeof(cases) / sizeof(t_test_case);
	while (++i < n)
		errors += run_test_case(&cases[i]);
	printf("--------------------------");
	printf("\n         SUMMARY");
	if (errors == 0)
		printf("\e[32m\nSuccessful tests: (%d/%d)\n\e[0m", n, n);
	else
		printf("\e[31m\nSuccessful tests: (%d/%d)\n\e[0m", n - errors, n);
	return (0);
}
