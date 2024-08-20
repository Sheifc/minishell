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
			|| strcmp(d->tokens[i]->value, c->tokens[i].value) != 0)
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
	free_tokens(data->tokens, &data->num_tokens);
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
	{T_COMMAND, "cd", 1}, {T_QUOTE, "\'", 1}, {T_TEXT, "/home|", 1},
	{T_QUOTE, "\'", 1}, {T_PAREN_CLOSE, ")", 1}}, 10},
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

// {"ls file?.txt", {{T_COMMAND, "ls", 1}, {T_WILDCARD, "*file*.txt", 1}}, 2},
// {"ls *file_[1-2].txt", {{T_COMMAND, "ls", 1}, {T_WILDCARD, "*file*.txt", 1}},
//  2},
// {"ls ?_file_[1-2].txt", {{T_COMMAND, "ls", 1},
// {T_WILDCARD, "*file*.txt", 1}}, 2},
// {"ls [a-b]_file_[1-2].txt", {{T_COMMAND, "ls", 1}, {T_WILDCARD, "*file*.txt",
//  1}}, 2}

// const char *input = "FRASE";
// int num_tokens;
// Token **tokens = tokenize(input, &num_tokens);

// printf("input:\n%s\n\n", input);
// print_tokens(tokens, num_tokens);
// printf("\n");

// {	"ls -la",
// 	{
// 		{T_COMMAND, "ls", 1},
// 		{T_ARG, "-la", 1}
// 	},
// 	2
// }

// {"ls *[1-2].txt",
// 	{
// 		{T_COMMAND, "ls", 1},
// 		{T_WILDCARD, "*[1-2].txt", 1}
// 	},
// 	2
// }

// {"ls -la && (cd /home || echo \"Failed change directory\") | grep 'file'",
// 	{
// 		{T_COMMAND, "ls", 1},
// 		{T_ARG, "-la", 1},
// 		{T_AND, "&&", 1},
// 		{T_PAREN_OPEN, "(", 1},
// 		{T_COMMAND, "cd", 1},
// 		{T_ARG, "/home", 1},
// 		{T_OR, "||", 1},
// 		{T_COMMAND, "echo", 1},
// 		{T_TEXT, "Failed change directory", 1},
// 		{T_PAREN_CLOSE, ")", 1},
// 		{T_PIPE, "|", 1},
// 		{T_COMMAND, "grep", 1},
// 		{T_TEXT, "file", 1}
// 	},
// 	13
// }

// 	const char			*test1 = "ls -la"
// 	const t_test_token	expected1[] = {
// 		{T_COMMAND, "ls", 1}, {T_ARG, "-la", 1}
// 	};

// 	const char *test2 = "ls -la && (cd /home || "
//		"echo \"Failed change directory\") | grep 'file'";
// 	const t_test_token expected2[] = {
// 		{T_COMMAND, "ls", 1},
// 		{T_ARG, "-la", 1},
// 		{T_AND, "&&", 1},
// 		{T_PAREN_OPEN, "(", 1},
// 		{T_COMMAND, "cd", 1},
// 		{T_ARG, "/home", 1},
// 		{T_OR, "||", 1},
// 		{T_COMMAND, "echo", 1},
// 		{T_TEXT, "Failed change directory", 1},
// 		{T_PAREN_CLOSE, ")", 1},
// 		{T_PIPE, "|", 1},
// 		{T_COMMAND, "grep", 1},
// 		{T_TEXT, "file", 1}
// 	};

// 	const char *test3 = "echo 'Hello, World!' | cat -n";
// 	const t_test_token expected3[] = {
// 		{T_COMMAND, "echo", 1},
// 		{T_TEXT, "Hello, World!", 1},
// 		{T_PIPE, "|", 1},
// 		{T_COMMAND, "cat", 1},
// 		{T_ARG, "-n", 1}
// 	};

// 	const char *test4 = "mkdir new_folder && cd new_folder";
// 	const t_test_token expected4[] = {
// 		{T_COMMAND, "mkdir", 1},
// 		{T_ARG, "new_folder", 1},
// 		{T_AND, "&&", 1},
// 		{T_COMMAND, "cd", 1},
// 		{T_ARG, "new_folder", 1}
// 	};

// 	const char *test5 = "(echo 'start'; ls) && (cd /tmp || echo 'Failed')";
// 	const t_test_token expected5[] = {
// 		{T_PAREN_OPEN, "(", 1},
// 		{T_COMMAND, "echo", 1},
// 		{T_TEXT, "start", 1},
// 		{T_SEMICOLON, ";", 1},
// 		{T_COMMAND, "ls", 1},
// 		{T_PAREN_CLOSE, ")", 1},
// 		{T_AND, "&&", 1},
// 		{T_PAREN_OPEN, "(", 1},
// 		{T_COMMAND, "cd", 1},
// 		{T_ARG, "/tmp", 1},
// 		{T_OR, "||", 1},
// 		{T_COMMAND, "echo", 1},
// 		{T_TEXT, "Failed", 1},
// 		{T_PAREN_CLOSE, ")", 1}
// 	};

// 	const char *test6 = "cat < input.txt";
// 	const t_test_token expected6[] = {
// 		{T_COMMAND, "cat", 1},
// 		{T_INPUT, "<", 1},
// 		{T_ARG, "input.txt", 1}
// 	};

// 	const char *test7 = "cat << EOF";
// 	const t_test_token expected7[] = {
// 		{T_COMMAND, "cat", 1},
// 		{T_HEREDOC, "<<", 1},
// 		{T_ARG, "EOF", 1}
// 	};

// 	const char *test8 = "echo Hello > output.txt";
// 	const t_test_token expected8[] = {
// 		{T_COMMAND, "echo", 1},
// 		{T_ARG, "Hello", 1},
// 		{T_OUTPUT, ">", 1},
// 		{T_ARG, "output.txt", 1}
// 	};

// 	const char *test9 = "echo Hello >> output.txt";
// 	const t_test_token expected9[] = {
// 		{T_COMMAND, "echo", 1},
// 		{T_ARG, "Hello", 1},
// 		{T_OUTPUT_APPEND, ">>", 1},
// 		{T_ARG, "output.txt", 1}
// 	};

// 	const char *test10 = "ls; cd /tmp; echo 'done';";
// 	const t_test_token expected10[] = {
// 		{T_COMMAND, "ls", 1},
// 		{T_SEMICOLON, ";", 1},
// 		{T_COMMAND, "cd", 1},
// 		{T_ARG, "/tmp", 1},
// 		{T_SEMICOLON, ";", 1},
// 		{T_COMMAND, "echo", 1},
// 		{T_TEXT, "done", 1},
// 		{T_SEMICOLON, ";", 1}
// 	};

//const char *test11 = "ls -la; (echo 'Hello'; cat < input.txt) && echo 'done'";
// 	const t_test_token expected11[] = {
// 		{T_COMMAND, "ls", 1},
// 		{T_ARG, "-la", 1},
// 		{T_SEMICOLON, ";", 1},
// 		{T_PAREN_OPEN, "(", 1},
// 		{T_COMMAND, "echo", 1},
// 		{T_TEXT, "Hello", 1},
// 		{T_SEMICOLON, ";", 1},
// 		{T_COMMAND, "cat", 1},
// 		{T_INPUT, "<", 1},
// 		{T_ARG, "input.txt", 1},
// 		{T_PAREN_CLOSE, ")", 1},
// 		{T_AND, "&&", 1},
// 		{T_COMMAND, "echo", 1},
// 		{T_TEXT, "done", 1}
// 	};

// 	const char *test12 = "(echo 'start' && ls) || (cd /tmp && echo 'Failed')";
// 	const t_test_token expected12[] = {
// 		{T_PAREN_OPEN, "(", 1},
// 		{T_COMMAND, "echo", 1},
// 		{T_TEXT, "start", 1},
// 		{T_AND, "&&", 1},
// 		{T_COMMAND, "ls", 1},
// 		{T_PAREN_CLOSE, ")", 1},
// 		{T_OR, "||", 1},
// 		{T_PAREN_OPEN, "(", 1},
// 		{T_COMMAND, "cd", 1},
// 		{T_ARG, "/tmp", 1},
// 		{T_AND, "&&", 1},
// 		{T_COMMAND, "echo", 1},
// 		{T_TEXT, "Failed", 1},
// 		{T_PAREN_CLOSE, ")", 1}
// 	};

// 	const char *test13 = "cat << EOF > output.txt";
// 	const t_test_token expected13[] = {
// 		{T_COMMAND, "cat", 1},
// 		{T_HEREDOC, "<<", 1},
// 		{T_ARG, "EOF", 1},
// 		{T_OUTPUT, ">", 1},
// 		{T_ARG, "output.txt", 1}
// 	};

// {"(ls -l -a -r | grep 'txt' && cat file.txt > output.txt || echo 'Failed')
// && ls *[1-2].txt",
// 	{
// 		{T_PAREN_OPEN, "(", 1},
// 		{T_COMMAND, "ls", 1},
// 		{T_ARG, "-l", 1},
// 		{T_ARG, "-a", 1},
// 		{T_ARG, "-r", 1},
// 		{T_PIPE, "|", 1},
// 		{T_COMMAND, "grep", 1},
// 		{T_TEXT, "txt", 1},
// 		{T_AND, "&&", 1},
// 		{T_COMMAND, "cat", 1},
// 		{T_ARG, "file.txt", 1},
// 		{T_OUTPUT, ">", 1},
// 		{T_ARG, "output.txt", 1},
// 		{T_OR, "||", 1},
// 		{T_COMMAND, "echo", 1},
// 		{T_TEXT, "Failed", 1},
// 		{T_PAREN_CLOSE, ")", 1},
// 		{T_AND, "&&", 1},
// 		{T_COMMAND, "ls", 1},
// 		{T_WILDCARD, "*[1-2].txt", 1}
// 	},
// 	20
// }

// 	const char *test14 = "    \t ";
// 	const t_test_token expected14[] = {
// 	};

// 	errors += run_test(test1, expected1, 2);
// 	errors += run_test(test2, expected2, 13);
// 	errors += run_test(test3, expected3, 5);
// 	errors += run_test(test4, expected4, 5);
// 	errors += run_test(test5, expected5, 14);
// 	errors += run_test(test6, expected6, 3);
// 	errors += run_test(test7, expected7, 3);
// 	errors += run_test(test8, expected8, 4);
// 	errors += run_test(test9, expected9, 4);
// 	errors += run_test(test10, expected10, 8);
// 	errors += run_test(test11, expected11, 14);
// 	errors += run_test(test12, expected12, 14);
// 	errors += run_test(test13, expected13, 5);
// 	errors += run_test(test14, expected14, 0);