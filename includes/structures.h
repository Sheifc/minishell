#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "ast.h"
# include "libft.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_cmd
{
	char			*name;
	char			**arg;
	int				n_args;
	int				fdin;
	int				fdout;
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
	int				tmpin;
	int				tmpout;
	pid_t			pid;
	int				cmd_count;
}					t_shell;

#endif