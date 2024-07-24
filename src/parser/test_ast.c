#include "syntax.h"

typedef struct _test_ast
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
	Token	**tokens;
	ASTNode	*ast;
	bool	is_valid;
	int		num_tokens;

	printf("\e[35m\n------------------- %d -------------------\n\e[0m", index);
	tokens = tokenize(test_value->inputs, &num_tokens);
	printf("input:\n%s\n\n", test_value->inputs);
	print_tokens(tokens, num_tokens);
	verify_tokens(tokens, &num_tokens);
	ast = build_ast(tokens, num_tokens, 0);
	printf("AST:\n");
	print_ast(ast);
	is_valid = validate_ast(tokens, ast);
	print_result(test_value->is_valid, is_valid);
	free_tokens(tokens, &num_tokens);
	free_ast(ast);
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
	{"export", true},
	{"ls -la | grep 'txt' && cat file.txt > output.txt", true},
	{"ls -la | grep 'txt' && cat file.txt >> output.txt || echo 'Failed'", true},
	{"(ls -l -a -r | grep 'txt') && (sort < input.txt || "
		"(echo 'Failed'&& mkdir new_dir))", true},
	{"mkdir test && cd test || echo 'Could not create directory'", true},
	{"echo 'Starting process'; (cd /tmp && touch temp_file) || "
		"echo 'Error in processing'", true},
	{"ls file*.txt", true}
	};
	const int			num_tests = sizeof(test_values) / sizeof(t_test_ast);

	i = -1;
	while (++i < num_tests)
		process_test_case(&test_values[i], i);
	return (0);
}
