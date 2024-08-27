/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:50:43 by sheferna          #+#    #+#             */
/*   Updated: 2024/08/27 18:50:44 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_H
# define SYNTAX_H

# include "ast.h"
# include "token.h"
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

// Syntax
bool	is_ast_valid(t_ast_node *root, int *status);
bool	validate_ast(t_token **tokens, t_ast_node *root, int *status);

// Syntax utils
bool	is_command_with_args(t_ast_node *node, int *status);
bool	is_command_with_args_mandatory(t_ast_node *node, int *status);
bool	is_binary_operator_valid(t_ast_node *node, int *status);
bool	is_redirection_valid(t_ast_node *node, int *status);

#endif