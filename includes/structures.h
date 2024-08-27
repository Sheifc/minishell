/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 19:19:19 by sheferna          #+#    #+#             */
/*   Updated: 2024/08/27 05:07:58 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "libft.h"
# include <stdbool.h>

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_ARGUMENT,
	NODE_PIPE,
	NODE_AND,
	NODE_OR,
	NODE_PARENTHESIS,
	NODE_INPUT,
	NODE_HEREDOC,
	NODE_OUTPUT,
	NODE_OUTPUT_APPEND,
	NODE_SEMICOLON,
	NODE_UNKNOWN,
	NODE_END,
	NODE_UNDEFINED
}						t_node_type;

typedef struct s_ast_node
{
	int					level;
	t_node_type			type;
	char				*value;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}						t_ast_node;

typedef enum e_token_type
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
}						t_token_type;

typedef struct s_token
{
	t_token_type		type;
	char				*value;
	bool				expect_arg;
}						t_token;

typedef struct s_word_features
{
	int					start;
	int					pos;
	bool				btw_quotes;
	bool				new_word;
}						t_word_features;

typedef enum e_redirect
{
	R_NONE,
	R_INFILE,
	R_OUTFILE
}						t_redirect;

typedef enum e_parenthesis
{
	P_NONE,
	P_OPEN,
	P_CLOSE
}						t_parenthesis;

typedef struct s_cmd
{
	char				*name;
	char				**arg;
	int					n_args;
	int					fdin;
	int					fdout;
	int					parenthesis;
	t_redirect			redirect;
	t_parenthesis		parenthesis_status;
	t_node_type			operator;
	struct s_cmd		*next;
}						t_cmd;

typedef struct s_shell
{
	t_token				**tokens;
	t_ast_node			*ast;
	t_cmd				*cmd;
	t_env				*env;
	t_env				*export;
	char				*prompt;
	char				**envp;
	char				*path;
	int					status;
	int					total_status;
	int					num_tokens;
	int					parenthesis;
	int					tmpin;
	int					tmpout;
	pid_t				pid;
	int					cmd_count;
}						t_shell;

#endif