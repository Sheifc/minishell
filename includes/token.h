#ifndef TOKEN_H
# define TOKEN_H

# include "libft.h"
# include <dirent.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define MAX_TOKENS 1000
# define DELIMITERS " \r\n\t\v\f"
# define NOMATCH -1

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
	T_QUOTE,
	T_PAREN_OPEN,
	T_PAREN_CLOSE,
	T_TEXT,
	T_INPUT,
	T_HEREDOC,
	T_OUTPUT,
	T_OUTPUT_APPEND,
	T_SEMICOLON,
	T_WILDCARD,
	T_REDIRECT_ARG,
	T_UNKNOWN
}				TokenType;

typedef struct _Token
{
	TokenType	type;
	char		*value;
	bool		expect_arg;
}				Token;

typedef struct _word_features
{
	int			start;
	int			pos;
	bool		btw_quotes;
	bool		new_word;
}				t_word_features;

// token
Token			*create_token(TokenType type, const char *value, bool exp_arg);
void			free_token2(Token *token);
int				verify_tokens(Token **tokens, int *n_tokens);
Token			**tokenize(const char *input, int *num_tokens);

// token_preprocess
char			*process_word(const char *input, int start, int length,
					char *output);
int				get_operation_size(const char *str);
void			handle_character(const char *input, char **output,
					t_word_features *ft);
bool			ok_count_quotes(const char *str);
char			*preprocess_input(const char *input);

// token_preprocess_utils
char			*remove_quotes(const char *input);
char			*add_quotes(const char *converted_word, char *quote);
char			*get_converted_word(const char *palabra, int longitud);
void			toggle_between_quotes(t_word_features *ft);
void			handle_spaces_and_operators(const char *in, char **output,
					t_word_features *ft);

// token_handles
void			handle_wildcards(char **start, Token **tokens, int *n_tokens);
void			handle_unmatched_quotes(char **start, char *end, Token **tokens,
					int *n_tokens);
void			handle_quotes(char **start, Token **tokens, int *n_tokens,
					char quote_char);
void			handle_redirect_arg(char **start, Token **tokens,
					int *n_tokens);
void			handle_regular_tokens(char **start, Token **tokens,
					int *n_tokens);

// token_handles_utils
bool			is_operator(const char *str);
void			handle_heredoc_token(char **start, Token **tokens,
					int *n_tokens);
void			handle_output_append_token(char **start, Token **tokens,
					int *n_tokens);
void			handle_input_token(char **start, Token **tokens, int *n_tokens);
void			handle_output_token(char **start, Token **tokens,
					int *n_tokens);

// token_utils
void			free_tokens(Token **tokens, int *num_tokens);
void			skip_delimiters(char **start);
void			add_token(char **start, Token **tokens, int *n_tokens, Token t);
void			add_cmd_arg_token(char **start, Token **tokens, int *n_tokens);
void			print_tokens(Token **tokens, int n_tokens);

// wildcard
int				match(const char *pattern, const char *string);
bool			is_wildcards(char **start);
bool			search_wildcard_matches(const char *wildcard, Token **tokens,
					int *n_tokens);

// wildcard_utils
int				handle_question(const char *pattern, const char *string);
int				handle_star(const char *pattern, const char *string);
int				handle_brackets(const char *pattern, const char *string);
int				handle_exact_match(const char *pattern, const char *string);

#endif