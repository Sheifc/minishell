/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 10:32:23 by svilla-d          #+#    #+#             */
/*   Updated: 2024/09/01 10:32:23 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

typedef struct s_test_ast
{
	char	inputs[100];
	bool	is_valid;
}			t_test_ast;

static void	print_result(bool expected, bool result)
{
	const char	*expected_str;
	const char	*result_str;

	if (expected)
		expected_str = "TRUE";
	else
		expected_str = "FALSE";
	if (result)
		result_str = "TRUE";
	else
		result_str = "FALSE";
	if (result == expected)
	{
		printf("\e[32m *Expected: %s ", expected_str);
		printf(" *Result: %s ", result_str);
		printf(" *Test: Ok\e[0m\n");
	}
	else
	{
		printf("\e[31m *Expected: %s ", expected_str);
		printf(" *Result: %s ", result_str);
		printf(" *Test: Failed\e[0m\n");
	}
}

void	process_test_case(const t_test_ast *test_value, int index)
{
	t_ast_node	*ast;
	t_shell		data;
	bool		is_valid;
	int			balance;

	printf("\e[35m\n------------------- %d -------------------\n\e[0m", index);
	data.prompt = ft_strdup(test_value->inputs);
	printf("input:\n%s\n\n", data.prompt);
	data.tokens = tokenize(&data);
	print_tokens(data.tokens, data.num_tokens);
	balance = verify_tokens(&data);
	ast = build_ast(data.tokens, data.num_tokens, 0);
	printf("AST:\n");
	print_ast(ast);
	is_valid = validate_ast(data.tokens, ast, &data.status);
	print_result(test_value->is_valid, is_valid && balance == 0);
	free_tokens(&data.tokens, &data.num_tokens);
	free_ast(&ast);
	free(data.prompt);
	printf("\n");
}

int	main(void)
{
	int					i;
	const t_test_ast	test_values[] = {
	{"cd .", true},
	{"() ()", false},
	{"() () ls -al", false},
	{"(ls -la", false},
	{"ls -la)", false},
	{"(ls -la)", true},
	{"ls -la |grep 'txt' && cat file.txt >> output.txt || echo 'Failed'", true},
	{"(ls -l -a -r | grep 'txt') && (sort < input.txt || "
		"(echo 'Failed' && mkdir new_dir))", true},
	{"mkdir test && cd test || echo 'Could not create directory'", true},
	{"echo 'Starting process'; (cd /tmp && touch temp_file) || "
		"echo 'Error in processing'", false},
	{"\"ls\" 'file*.txt' && \'ls\' file*.txt", true},
	{"\"ls 'file*.txt' && ls file*.txt", false},
	{"\"e\"cho \'hola m\'u\'n\"\"do\' \"chao mundo\"", true},
	{"ls | (pwd && echo '/home|' $USERS {$USER} '$USER' )", true}
	};
	const int			num_tests = sizeof(test_values) / sizeof(t_test_ast);

	i = -1;
	while (++i < num_tests)
		process_test_case(&test_values[i], i);
	return (0);
}
