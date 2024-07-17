#ifndef AST_H
# define AST_H

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
# define M_TEXT "Text"
# define M_INPUT "Redirect"
# define M_HEREDOC "Redirect"
# define M_OUTPUT "Redirect"
# define M_OUTPUT_APPEND "Redirect"
# define M_SEMICOLON "Semicolon"
# define M_UNKNOWN "Unknown"

# define OK 0
# define NOT_FOUND -1
# define ERROR -2

// Command
typedef struct _Command
{
	char			*name;
	char			**args;
	int				arg_count;
}					Command;

typedef enum _NodeType
{
	NODE_COMMAND,
	NODE_ARGUMENT,
	NODE_PIPE,
	NODE_AND,
	NODE_OR,
	NODE_PARENTHESIS,
	NODE_TEXT,
	NODE_INPUT,
	NODE_HEREDOC,
	NODE_OUTPUT,
	NODE_OUTPUT_APPEND,
	NODE_SEMICOLON,
	NODE_UNKNOWN
}					NodeType;

typedef struct _ASTNode
{
	int				level;
	NodeType		type;
	char			*value;
	struct _ASTNode	*left;
	struct _ASTNode	*right;
}					ASTNode;

// AST
ASTNode				*create_node(NodeType type, char *value, int level);
void				free_ast(ASTNode *root);
ASTNode				*build_ast(Token **tokens, int num_tokens, int level);

// AST handles
ASTNode				*build_redirect_node(Token *token, int level);
ASTNode				*build_command_node(Token **tokens, int n_token, int level);
ASTNode				*handle_operators(Token **tokens, int n_token, int level,
						int *pos);
ASTNode				*handle_parentheses(Token **tokens, int n_token, int level);
ASTNode				*handle_redirection(Token **tokens, int n_token, int level);

// AST utils
int					find_matching_paren(Token **tokens, int start, int n_token);
NodeType			select_redirection(TokenType type);
NodeType			select_operator(TokenType type);
int					find_operator(Token **tokens, int num_tokens);
void				print_ast(ASTNode *root);

#endif