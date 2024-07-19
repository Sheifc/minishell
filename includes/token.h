#ifndef TOKEN_H
# define TOKEN_H

# include "libft.h"
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define MAX_TOKENS 1000
# define DELIMITERS " \r\n\t\v\f"

// TokenType:
// 	T_COMMAND			commands
// 	T_ARG				arguments
// 	T_PIPE				|
// 	T_AND				&&
// 	T_OR				||
// 	T_PAREN_OPEN		(
// 	T_PAREN_CLOSE		)
// 	T_TEXT				"..."
// 	T_INPUT				<
// 	T_HEREDOC			<<
// 	T_OUTPUT			>
// 	T_OUTPUT_APPEND		>>
// 	T_SEMICOLON			;
//  T_WILDCARD			*?[]
// 	T_UNKNOWN

typedef enum _TokenType
{
	T_COMMAND,
	T_ARG,
	T_PIPE,
	T_AND,
	T_OR,
	T_PAREN_OPEN,
	T_PAREN_CLOSE,
	T_TEXT,
	T_INPUT,
	T_HEREDOC,
	T_OUTPUT,
	T_OUTPUT_APPEND,
	T_SEMICOLON,
	T_WILDCARD,
	T_UNKNOWN
}				TokenType;

typedef struct _Token
{
	TokenType	type;
	char		*value;
	bool		expect_arg;
}				Token;

// token
Token			*create_token(TokenType type, const char *value, bool exp_arg);
void			free_token2(Token *token);
Token			**tokenize(const char *input, int *num_tokens);

// token_handles
void			handle_wildcards(char **start, Token **tokens, int *n_tokens);
void			handle_quotes(char **start, Token **tokens, int *n_tokens,
					char quote_char);
void			handle_regular_tokens(char **start, Token **tokens,
					int *n_tokens);

// token_utils
void			free_tokens(Token **tokens, int num_tokens);
void			skip_delimiters(char **start);
void			add_token(char **start, Token **tokens, int *n_tokens, Token t);
void			add_cmd_arg_token(char **start, Token **tokens, int *n_tokens);
void			print_tokens(Token **tokens, int n_tokens);

#endif