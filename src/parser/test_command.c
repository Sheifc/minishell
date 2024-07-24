#include "command.h"

int	main(void)
{
	const char	*input;
	Token		**tokens;
	ASTNode		*ast;
	bool		is_valid;
	int			num_tokens;

	input = "ls file*.txt | wc > out1.txt >> out2.txt > out3.txt >> out4.txt ";
	printf("\e[35m\n------------------- * -------------------\n\e[0m");
	tokens = tokenize(input, &num_tokens);
	printf("input:\n%s\n", input);
	printf("\n**** Tokens: ****\n");
	print_tokens(tokens, num_tokens);
	verify_tokens(tokens, &num_tokens);
	ast = build_ast(tokens, num_tokens, 0);
	printf("\n**** AST: ****\n");
	print_ast(ast);
	is_valid = validate_ast(tokens, ast);
	printf("\n**** Exe: ****\n");
	if (is_valid)
		traverse_ast(ast, STDIN_FILENO, STDOUT_FILENO);
	return (0);
}

// input = "((ls file* | wc) && (ls arch* | wc -l) && ls arch*.txt) | wc";
