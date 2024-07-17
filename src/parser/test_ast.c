# include "syntax.h"
typedef struct _test_ast
{
	char inputs[100];
	bool isValid;
} t_test_ast;

int main() {
	t_test_ast test_values[] = {
		{"() ()", false},
		{"() () ls -al", false},
		{"(ls -la", false},
		{"ls -la)", false},
		{"(ls -la)", true},
		{"ls -la | grep 'txt' && cat file.txt > output.txt", true},
		{"ls -la | grep 'txt' && cat file.txt > output.txt || echo 'Failed'", true},
		{"(ls -l -a -r | grep 'txt') && (cat file.txt > output.txt || (echo 'Failed' && mkdir new_dir))", true},
		{"mkdir test && cd test || echo 'Could not create directory'", true},
		{"echo 'Starting process'; (cd /tmp && touch temp_file) || echo 'Error in processing'", true}
	};

	for (int i = 0; i < 10; i++) {
		printf("\n-------------- %d --------------\n", i);
		char *input = test_values[i].inputs;
		bool expected = test_values[i].isValid;
		int num_tokens;
		bool is_valid;
		Token **tokens = tokenize(input, &num_tokens);

		printf("input:\n%s\n\n", input);
		print_tokens(tokens, num_tokens);
		printf("\n");

		ASTNode *ast = build_ast(tokens, num_tokens, 0);
		printf("AST:\n");
		print_ast(ast);
		printf("\n");

		is_valid = validate_ast(tokens, ast);
		printf("\nAST Valid\n");
		printf(" *Expected: %s ", expected ? "TRUE" : "FALSE");
		printf(" *Result: %s ", is_valid ? "TRUE" : "FALSE");
		printf(" *Test: %s\n", is_valid == expected? "Ok" : "Failed");

		for (int i = 0; i < num_tokens; i++)
			if (tokens[i])
				free_token2(tokens[i]);
		free(tokens);
		free_ast(ast);
		printf("\n");
	}
	return 0;
}
