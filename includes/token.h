#ifndef TOKEN_H
# define TOKEN_H

# include "error.h"
# include "libft.h"
# include "structures.h"
# include <ctype.h>
# include <dirent.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define MAX_TOKENS 1000
# define MAX_LENGTH 8192
# define DELIMITERS " \r\n\t\v\f"
# define NOMATCH -1

// token
Token	*create_token(TokenType type, const char *value, bool exp_arg);
void	free_token(Token **token);
int		verify_tokens(t_shell *data);
Token	**process_tokens(t_shell *data, char *input_copy);
Token	**tokenize(t_shell *data);

// token_preprocess
char	*process_word(const char *input, int start, int length, char *output);
int		get_operation_size(const char *str);
void	handle_character(const char *input, char **output, t_word_features *ft);
bool	ok_count_quotes(const char *str);
char	*preprocess_input(const char *input, t_word_features feat, t_shell *data);

// token_preprocess_utils
char	*remove_quotes(const char *input);
char	*add_quotes(const char *converted_word, char *quote);
char	*get_converted_word(const char *palabra, int longitud);
void	toggle_between_quotes(t_word_features *ft);
void	handle_spaces_and_operators(const char *in, char **output,
			t_word_features *ft);

// token_env
char	*initialize_result(const char *input);
char	*extract_variable_name(const char *start);
char	*replace_variable(const char *pos, char *result, const char *var_name, t_shell *data);
int		is_btw_single_quotes(const char *str, const char *pos);
char	*replace_env_variables(const char *input, t_shell *data);

// token_handles
int		handle_wildcards(char **start, t_shell *data, TokenType type);
void	handle_unmatched_quotes(char **start, char *end, Token **tokens,
			int *n_tokens);
void	handle_quotes(char **start, Token **tokens, int *n_tokens,
			char quote_char);
int		handle_redirect_arg(char **start, t_shell *data);
int		handle_regular_tokens(char **start, t_shell *data);

// token_handles_utils
bool	is_operator(const char *str);
int		handle_heredoc_token(char **start, t_shell *data);
int		handle_output_append_token(char **start, t_shell *data);
int		handle_input_token(char **start, t_shell *data);
int		handle_output_token(char **start, t_shell *data);

// token_utils
void	free_tokens(Token **tokens, int *num_tokens);
void	skip_delimiters(char **start);
int		add_token(char **start, t_shell *data, Token t);
int		add_cmd_arg_token(char **start, t_shell *data);
void	print_tokens(Token **tokens, int n_tokens);

// wildcard
int		match(const char *pattern, const char *string);
int		search_wildcard_matches(const char *wildcard, t_shell *data,
			TokenType type);
bool	is_wildcards(char **start);

// wildcard_utils
int		char_in_set(char c, const char *set);
int		handle_question(const char *pattern, const char *string);
int		handle_star(const char *pattern, const char *string);
int		handle_brackets(const char *pattern, const char *string);
int		handle_exact_match(const char *pattern, const char *string);

#endif