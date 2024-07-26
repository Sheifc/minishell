#include "minishell.h"

void	lexer(char *prompt, t_token **tok)
{
	int	i;
	// Token	**tokens;
	// ASTNode	*ast;
	// bool	is_valid;
	// int		num_tokens;
	// int		balance;
	// Command	*cmd = NULL;
	// Command		*current = NULL;
	// OperatorStack *ope_stack = NULL;
	// PipeStack *pipe_stack = NULL;

	// ast = NULL;
	// printf("\e[35m\n------------------- * -------------------\n\e[0m");
	// tokens = tokenize(prompt, &num_tokens);
	// printf("input:\n%s\n\n", prompt);
	// print_tokens(tokens, num_tokens);
	// balance = verify_tokens(tokens, &num_tokens);
	// if (balance == 0)
	// {
	// 	ast = build_ast(tokens, num_tokens, 0);
	// 	printf("AST:\n");
	// 	print_ast(ast);
	// 	is_valid = validate_ast(tokens, ast);
	// 	printf("Es válido: %d\n",is_valid);
	// 	if (is_valid)
	// 	{
	// 		cmd = traverse_ast(ast, STDIN_FILENO, STDOUT_FILENO, &ope_stack, &pipe_stack);
	// 		current = cmd;
	// 		printf("\n**** Commands: ****\n");
	// 		while (current)
	// 		{
	// 			print_command(current);
	// 			current = current->next;
	// 		}
	// 	}
	// }
	// free_tokens(tokens, &num_tokens);
	// free_ast(ast);
	// printf("\e[35m\n------------------- * -------------------\e[0m\n\n");

	i = 0;
	while (prompt[i])
	{
		if (prompt[i] == '|')
			set_token(PIPE, prompt, tok, &i);
		else if (prompt[i] == '<')
			set_token(IN, prompt, tok, &i);
		else if (prompt[i] == '>')
			set_token(OUT, prompt, tok, &i);
		else if (prompt[i] == '\'')
			set_token(QUOTE, prompt, tok, &i);
		else if (prompt[i] == '"')
			set_token(DQUOTE, prompt, tok, &i);
		else if (prompt[i] != '|' && prompt[i] != '<' && prompt[i] != '>'
			&& prompt[i] != '\'' && prompt[i] != '"' && prompt[i] != ' ')
			set_token(WORD, prompt, tok, &i);
		else
			i++;
	}
}
