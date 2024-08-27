/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:49:42 by sheferna          #+#    #+#             */
/*   Updated: 2024/08/27 18:49:43 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "structures.h"
# include "token.h"
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define M_COMMAND "Command"
# define M_ARGUMENT "Argument"
# define M_PIPE "Pipe"
# define M_AND "And"
# define M_OR "Or"
# define M_PAREN "Parentesis"
# define M_INPUT "Input"
# define M_HEREDOC "Heredoc"
# define M_OUTPUT "Output"
# define M_OUTPUT_APPEND "Output_append"
# define M_SEMICOLON "Semicolon"
# define M_UNKNOWN "Unknown"

# define OPE_COMMAND "COMMAND"
# define OPE_ARGUMENT "ARGUMENT"
# define OPE_PIPE "|"
# define OPE_AND "&&"
# define OPE_OR "||"
# define OPE_PAREN "()"
# define OPE_INPUT "<"
# define OPE_HEREDOC "<<"
# define OPE_OUTPUT ">"
# define OPE_OUTPUT_APPEND ">>"
# define OPE_SEMICOLON ";"
# define OPE_UNKNOWN "UNKNOWN"
# define OPE_END "END"
# define OPE_UNDEFINED "UNDEFINED"

# define OK 0
# define NOT_FOUND -1
# define ERROR -2

// AST
t_ast_node	*create_node(t_node_type type, char *value, int level);
void		ft_free_str(char **str);
void		free_ast(t_ast_node **root);
t_ast_node	*build_ast(t_token **tokens, int num_tokens, int level);

// AST handles
t_ast_node	*build_redirect_node(t_token **tokens, char *name, int num_tokens,
				int level);
t_ast_node	*build_command_node(t_token **tokens, int n_token, int level);
t_ast_node	*handle_operators(t_token **tokens, int n_token, int level,
				int *pos);
t_ast_node	*handle_parentheses(t_token **tokens, int n_token, int level);
t_ast_node	*handle_redirection(t_token **tokens, int n_token, int level);

// AST utils
int			find_matching_paren(t_token **tokens, int start, int n_token);
const char	*node_type_to_symbol(t_node_type type);
t_node_type	select_operator(t_token_type type);
int			find_operator(t_token **tokens, int num_tokens);
void		print_ast(t_ast_node *root);

#endif