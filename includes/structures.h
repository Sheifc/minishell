#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "libft.h"
# include <stdbool.h>

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef enum _NodeType
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
}					NodeType;

typedef struct _ASTNode
{
	int				level;
	NodeType		type;
	char			*value;
	struct _ASTNode	*left;
	struct _ASTNode	*right;
}					ASTNode;

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
}					TokenType;

typedef struct _Token
{
	TokenType		type;
	char			*value;
	bool			expect_arg;
}					Token;

typedef struct _word_features
{
	int				start;
	int				pos;
	bool			btw_quotes;
	bool			new_word;
}					t_word_features;

typedef enum s_redirect
{
	R_NONE,
	R_INFILE,
	R_OUTFILE
}					t_redirect;

typedef struct s_cmd
{
	char			*name;
	char			**arg;
	int				n_args;
	int				fdin;
	int				fdout;
	t_redirect		redirect;
	struct s_cmd	*next;
	NodeType		operator;
}					t_cmd;

typedef struct s_shell
{
	Token			**tokens;
	ASTNode			*ast;
	t_cmd			*cmd;
	t_env			*env;
	t_env			*export;
	char			*prompt;
	char			**envp;
	char			*path;
	int				status;
	int				num_tokens;
	int				tmpin;
	int				tmpout;
	pid_t			pid;
	int				cmd_count;
}					t_shell;

#endif