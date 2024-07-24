#include "token.h"

void	handle_heredoc_token(char **start, Token **tokens, int *n_tokens)
{
	add_token(start, tokens, n_tokens, (Token){T_HEREDOC, "<<", true});
	handle_redirect_arg(start, tokens, n_tokens);
}

void	handle_output_append_token(char **start, Token **tokens, int *n_tokens)
{
	add_token(start, tokens, n_tokens, (Token){T_OUTPUT_APPEND, ">>", true});
	handle_redirect_arg(start, tokens, n_tokens);
}

void	handle_input_token(char **start, Token **tokens, int *n_tokens)
{
	add_token(start, tokens, n_tokens, (Token){T_INPUT, "<", true});
	handle_redirect_arg(start, tokens, n_tokens);
}

void	handle_output_token(char **start, Token **tokens, int *n_tokens)
{
	add_token(start, tokens, n_tokens, (Token){T_OUTPUT, ">", true});
	handle_redirect_arg(start, tokens, n_tokens);
}
