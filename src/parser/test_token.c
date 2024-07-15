# include "token.h"

int run_test(const char *input, const char *expected_tokens[][2], int expected_num_tokens) {
	bool error = false;
	int num_tokens;
	Token **tokens = tokenize(input, &num_tokens);

	printf("Input: %s\n", input);
	if (tokens)
	{
		if (num_tokens != expected_num_tokens) {
			error = true;
			printf(" -> Test failed: Number of tokens (%d) does not match expected (%d)\n", num_tokens, expected_num_tokens);
		}
		for (int i = 0; i < num_tokens; i++) {
			printf("Input    Token %d: Type = %d, Value = %s\n", i, tokens[i]->type, tokens[i]->value);
			if (i < expected_num_tokens) {
				printf("Expected Token %d: Type = %s, Value = %s\n", i, expected_tokens[i][0], expected_tokens[i][1]);
			}
			if (tokens[i]->type != atoi(expected_tokens[i][0]) || strcmp(tokens[i]->value, expected_tokens[i][1]) != 0) {
				error = true;
				printf(" -> Test failed: Token %d does not match expected\n", i);
			}
		}

		for (int i = 0; i < num_tokens; i++)
			if (tokens[i])
				free_token2(tokens[i]);
		free(tokens);   
	}
	if (error == false)
	{
		printf("All test: ok\n");
		printf("\n");
		return (0);
	}
	printf("\n");
	return (1);
}


int main() {
	int total_error = 0;
	const char *test1 = "ls -la";
	const char *expected1[][2] = {
		{"0", "ls"},
		{"1", "-la"}
	};

	const char *test2 = "ls -la && (cd /home || echo \"Failed to change directory\") | grep 'file'";
	const char *expected2[][2] = {
		{"0", "ls"},
		{"1", "-la"},
		{"4", "&&"},
		{"6", "("},
		{"0", "cd"},
		{"1", "/home"},
		{"5", "||"},
		{"0", "echo"},
		{"8", "Failed to change directory"},
		{"7", ")"},
		{"3", "|"},
		{"0", "grep"},
		{"8", "file"}
	};

	const char *test3 = "echo 'Hello, World!' | cat -n";
	const char *expected3[][2] = {
		{"0", "echo"},
		{"8", "Hello, World!"},
		{"3", "|"},
		{"0", "cat"},
		{"1", "-n"}
	};

	const char *test4 = "mkdir new_folder && cd new_folder";
	const char *expected4[][2] = {
		{"0", "mkdir"},
		{"1", "new_folder"},
		{"4", "&&"},
		{"0", "cd"},
		{"1", "new_folder"}
	};

	const char *test5 = "(echo 'start'; ls) && (cd /tmp || echo 'Failed')";
	const char *expected5[][2] = {
		{"6", "("},
		{"0", "echo"},
		{"8", "start"},
		{"13", ";"},
		{"0", "ls"},
		{"7", ")"},
		{"4", "&&"},
		{"6", "("},
		{"0", "cd"},
		{"1", "/tmp"},
		{"5", "||"},
		{"0", "echo"},
		{"8", "Failed"},
		{"7", ")"}
	};

	const char *test6 = "cat < input.txt";
	const char *expected6[][2] = {
		{"0", "cat"},
		{"9", "<"},
		{"1", "input.txt"}
	};

	const char *test7 = "cat << EOF";
	const char *expected7[][2] = {
		{"0", "cat"},
		{"10", "<<"},
		{"1", "EOF"}
	};

	const char *test8 = "echo Hello > output.txt";
	const char *expected8[][2] = {
		{"0", "echo"},
		{"1", "Hello"},
		{"11", ">"},
		{"1", "output.txt"}
	};

	const char *test9 = "echo Hello >> output.txt";
	const char *expected9[][2] = {
		{"0", "echo"},
		{"1", "Hello"},
		{"12", ">>"},
		{"1", "output.txt"}
	};

	const char *test10 = "ls; cd /tmp; echo 'done';";
	const char *expected10[][2] = {
		{"0", "ls"},
		{"13", ";"},
		{"0", "cd"},
		{"1", "/tmp"},
		{"13", ";"},
		{"0", "echo"},
		{"8", "done"},
		{"13", ";"}
	};

	const char *test11 = "ls -la; (echo 'Hello'; cat < input.txt) && echo 'done'";
	const char *expected11[][2] = {
		{"0", "ls"},
		{"1", "-la"},
		{"13", ";"},
		{"6", "("},
		{"0", "echo"},
		{"8", "Hello"},
		{"13", ";"},
		{"0", "cat"},
		{"9", "<"},
		{"1", "input.txt"},
		{"7", ")"},
		{"4", "&&"},
		{"0", "echo"},
		{"8", "done"}
	};

	const char *test12 = "(echo 'start' && ls) || (cd /tmp && echo 'Failed')";
	const char *expected12[][2] = {
		{"6", "("},
		{"0", "echo"},
		{"8", "start"},
		{"4", "&&"},
		{"0", "ls"},
		{"7", ")"},
		{"5", "||"},
		{"6", "("},
		{"0", "cd"},
		{"1", "/tmp"},
		{"4", "&&"},
		{"0", "echo"},
		{"8", "Failed"},
		{"7", ")"}
	};

	const char *test13 = "cat << EOF > output.txt";
	const char *expected13[][2] = {
		{"0", "cat"},
		{"10", "<<"},
		{"1", "EOF"},
		{"11", ">"},
		{"1", "output.txt"}
	};

	const char *test14 = "    \t ";
	const char *expected14[][2] = {
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
	printf("\nSuccessful tests: (%d/14)\n", 14 - total_error);

	return 0;
}