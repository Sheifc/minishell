# include "token.h"

typedef struct _test_token
{
	TokenType	type;
	char		value[100];
}				t_test_token;

int run_test(const char *input, const t_test_token	expected[], int expected_num_tokens) {
	bool error = false;
	int num_tokens;
	Token **tokens = tokenize(input, &num_tokens);

	printf("Input: %s\n", input);
	if (tokens)
	{
		if (num_tokens != expected_num_tokens) {
			error = true;
			printf("\e[31m -> Test failed: Number of tokens (%d) does not match expected (%d)\n\e[0m", num_tokens, expected_num_tokens);
		}
		for (int i = 0; i < num_tokens; i++) {
			printf("Input    Token %d: Type = %d, Value = %s\n", i, tokens[i]->type, tokens[i]->value);
			if (i < expected_num_tokens) {
				printf("Expected Token %d: Type = %d, Value = %s\n", i, expected[i].type, expected[i].value);
			}
			if (tokens[i]->type != expected[i].type || strcmp(tokens[i]->value, expected[i].value) != 0) {
				error = true;
				printf("\e[31m -> Test failed: Token %d does not match expected\n\e[0m", i);
			}
		}
		free_tokens(tokens, num_tokens);  
	}
	if (error == false)
	{
		printf("\e[32mAll test: ok\n\e[0m");
		printf("\n");
		return (0);
	}
	printf("\n");
	return (1);
}


int main() {
	int					total_error = 0;
	const char			*test1 = "ls -la";
	const t_test_token	expected1[] = {
		{T_COMMAND, "ls"}, {T_ARG, "-la"}
	};

	const char *test2 = "ls -la && (cd /home || echo \"Failed to change directory\") | grep 'file'";
	const t_test_token expected2[] = {
		{T_COMMAND, "ls"},
		{T_ARG, "-la"},
		{T_AND, "&&"},
		{T_PAREN_OPEN, "("},
		{T_COMMAND, "cd"},
		{T_ARG, "/home"},
		{T_OR, "||"},
		{T_COMMAND, "echo"},
		{T_TEXT, "Failed to change directory"},
		{T_PAREN_CLOSE, ")"},
		{T_PIPE, "|"},
		{T_COMMAND, "grep"},
		{T_TEXT, "file"}
	};

	const char *test3 = "echo 'Hello, World!' | cat -n";
	const t_test_token expected3[] = {
		{T_COMMAND, "echo"},
		{T_TEXT, "Hello, World!"},
		{T_PIPE, "|"},
		{T_COMMAND, "cat"},
		{T_ARG, "-n"}
	};

	const char *test4 = "mkdir new_folder && cd new_folder";
	const t_test_token expected4[] = {
		{T_COMMAND, "mkdir"},
		{T_ARG, "new_folder"},
		{T_AND, "&&"},
		{T_COMMAND, "cd"},
		{T_ARG, "new_folder"}
	};

	const char *test5 = "(echo 'start'; ls) && (cd /tmp || echo 'Failed')";
	const t_test_token expected5[] = {
		{T_PAREN_OPEN, "("},
		{T_COMMAND, "echo"},
		{T_TEXT, "start"},
		{T_SEMICOLON, ";"},
		{T_COMMAND, "ls"},
		{T_PAREN_CLOSE, ")"},
		{T_AND, "&&"},
		{T_PAREN_OPEN, "("},
		{T_COMMAND, "cd"},
		{T_ARG, "/tmp"},
		{T_OR, "||"},
		{T_COMMAND, "echo"},
		{T_TEXT, "Failed"},
		{T_PAREN_CLOSE, ")"}
	};

	const char *test6 = "cat < input.txt";
	const t_test_token expected6[] = {
		{T_COMMAND, "cat"},
		{T_INPUT, "<"},
		{T_ARG, "input.txt"}
	};

	const char *test7 = "cat << EOF";
	const t_test_token expected7[] = {
		{T_COMMAND, "cat"},
		{T_HEREDOC, "<<"},
		{T_ARG, "EOF"}
	};

	const char *test8 = "echo Hello > output.txt";
	const t_test_token expected8[] = {
		{T_COMMAND, "echo"},
		{T_ARG, "Hello"},
		{T_OUTPUT, ">"},
		{T_ARG, "output.txt"}
	};

	const char *test9 = "echo Hello >> output.txt";
	const t_test_token expected9[] = {
		{T_COMMAND, "echo"},
		{T_ARG, "Hello"},
		{T_OUTPUT_APPEND, ">>"},
		{T_ARG, "output.txt"}
	};

	const char *test10 = "ls; cd /tmp; echo 'done';";
	const t_test_token expected10[] = {
		{T_COMMAND, "ls"},
		{T_SEMICOLON, ";"},
		{T_COMMAND, "cd"},
		{T_ARG, "/tmp"},
		{T_SEMICOLON, ";"},
		{T_COMMAND, "echo"},
		{T_TEXT, "done"},
		{T_SEMICOLON, ";"}
	};

	const char *test11 = "ls -la; (echo 'Hello'; cat < input.txt) && echo 'done'";
	const t_test_token expected11[] = {
		{T_COMMAND, "ls"},
		{T_ARG, "-la"},
		{T_SEMICOLON, ";"},
		{T_PAREN_OPEN, "("},
		{T_COMMAND, "echo"},
		{T_TEXT, "Hello"},
		{T_SEMICOLON, ";"},
		{T_COMMAND, "cat"},
		{T_INPUT, "<"},
		{T_ARG, "input.txt"},
		{T_PAREN_CLOSE, ")"},
		{T_AND, "&&"},
		{T_COMMAND, "echo"},
		{T_TEXT, "done"}
	};

	const char *test12 = "(echo 'start' && ls) || (cd /tmp && echo 'Failed')";
	const t_test_token expected12[] = {
		{T_PAREN_OPEN, "("},
		{T_COMMAND, "echo"},
		{T_TEXT, "start"},
		{T_AND, "&&"},
		{T_COMMAND, "ls"},
		{T_PAREN_CLOSE, ")"},
		{T_OR, "||"},
		{T_PAREN_OPEN, "("},
		{T_COMMAND, "cd"},
		{T_ARG, "/tmp"},
		{T_AND, "&&"},
		{T_COMMAND, "echo"},
		{T_TEXT, "Failed"},
		{T_PAREN_CLOSE, ")"}
	};

	const char *test13 = "cat << EOF > output.txt";
	const t_test_token expected13[] = {
		{T_COMMAND, "cat"},
		{T_HEREDOC, "<<"},
		{T_ARG, "EOF"},
		{T_OUTPUT, ">"},
		{T_ARG, "output.txt"}
	};

	const char *test14 = "    \t ";
	const t_test_token expected14[] = {
	};

	total_error += run_test(test1, expected1, 2);
	total_error += run_test(test2, expected2, 13);
	total_error += run_test(test3, expected3, 5);
	total_error += run_test(test4, expected4, 5);
	total_error += run_test(test5, expected5, 14);
	total_error += run_test(test6, expected6, 3);
	total_error += run_test(test7, expected7, 3);
	total_error += run_test(test8, expected8, 4);
	total_error += run_test(test9, expected9, 4);
	total_error += run_test(test10, expected10, 8);
	total_error += run_test(test11, expected11, 14);
	total_error += run_test(test12, expected12, 14);
	total_error += run_test(test13, expected13, 5);
	total_error += run_test(test14, expected14, 0);

	printf("--------------------------");
	printf("\n         SUMMARY");
	if (total_error == 0)
		printf("\e[32m\nSuccessful tests: (%d/14)\n\e[0m", 14 - total_error);
	else
		printf("\e[31m\nSuccessful tests: (%d/14)\n\e[0m", 14 - total_error);

	return 0;
}