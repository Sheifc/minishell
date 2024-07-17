#ifndef SYNTAX_H
# define SYNTAX_H

# include "ast.h"
# include "token.h"
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

// Syntax
bool	is_ast_valid(ASTNode *root);
bool	validate_ast(Token **tokens, ASTNode *root);

// Syntax utils
bool	is_command_with_args(ASTNode *node);
bool	is_command_with_args_mandatory(ASTNode *node);
bool	is_binary_operator_valid(ASTNode *node);
bool	is_redirection_valid(ASTNode *node);

#endif