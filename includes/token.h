/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:50:48 by sheferna          #+#    #+#             */
/*   Updated: 2024/08/27 18:50:49 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
t_token	*create_token(t_token_type type, const char *value, bool exp_arg,
			t_shell *data);
void	free_token(t_token **token);
int		verify_tokens(t_shell *data);
t_token	**process_tokens(t_shell *data, char *input_copy);
t_token	**tokenize(t_shell *data);

// token_preprocess
char	*process_word(const char *input, int start, int length, char *output);
int		get_operation_size(const char *str);
void	handle_character(const char *input, char **output, t_word_features *ft);
int		count_quotes(const char *str);

// token_preprocess_utils
char	*remove_quotes(const char *input);
char	*add_quotes(const char *converted_word, char *quote);
char	*get_converted_word(const char *palabra, int longitud);
void	toggle_between_quotes(t_word_features *ft);
void	handle_spaces_and_operators(const char *in, char **output,
			t_word_features *ft);

// token_env
char	*create_new_result(const char *result, const char *pos,
			const char *value, const char *name);
char	*replace_variable(const char *pos, char *result, const char *var_name,
			t_shell *data);
bool	is_btw_single_quotes(const char *str, const char *pos);
int		is_preceded_by_double_less(const char *str, const char *pos);
char	*replace_env_variables(const char *input, t_shell *data);

// token_env_utils
char	*initialize_result(const char *input);
char	*extract_variable_name(const char *start);

// token_handles
int		handle_wildcards(char **start, t_shell *data, t_token_type type);
void	handle_unmatched_quotes(char **start, char *end, t_shell *data);
void	handle_quotes(char **start, char **end);
int		handle_redirect_arg(char **start, t_shell *data);
int		handle_regular_tokens(char **start, t_shell *data);

// token_handles_utils
int		handle_token(char **start, t_shell *data, t_token_type type,
			char *value);
char	*parse_string(const char *input, t_shell *data);
int		add_redirect_token(t_shell *data, char **start, char *end);

// token_utils
void	free_tokens(t_token ***tokens, int *num_tokens);
void	skip_delimiters(char **start);
int		add_token(char **start, t_shell *data, t_token t);
int		add_cmd_arg_token(char **start, t_shell *data);
void	print_tokens(t_token **tokens, int n_tokens);

// wildcard
int		match(const char *pattern, const char *string);
int		process_directory_entries(DIR *dir, const char *wildcard, t_shell *data,
			t_token_type type);
int		search_wildcard_matches(const char *wildcard, t_shell *data,
			t_token_type type);
bool	is_wildcards(char **start);

// wildcard_utils
int		char_in_set(char c, const char *set);
int		handle_question(const char *pattern, const char *string);
int		handle_star(const char *pattern, const char *string);
int		handle_brackets(const char *pattern, const char *string);
int		handle_exact_match(const char *pattern, const char *string);

// wildcard_preprocess
char	*remove_repeated_chars(const char *str, char ch);

#endif