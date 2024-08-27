/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:45:38 by sheferna          #+#    #+#             */
/*   Updated: 2024/08/27 18:45:41 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

// Function to find the corresponding closing parenthesis
int	find_matching_paren(t_token **tokens, int start, int num_tokens)
{
	int	depth;
	int	i;

	depth = 1;
	i = start + 1;
	while (i < num_tokens)
	{
		if (tokens[i]->type == T_PAREN_OPEN)
			depth++;
		else if (tokens[i]->type == T_PAREN_CLOSE)
		{
			depth--;
			if (depth == 0)
				return (i);
		}
		i++;
	}
	return (NOT_FOUND);
}

// Function to select the type of redirection
const char	*node_type_to_symbol(t_node_type type)
{
	const char	*symbol[] = {OPE_COMMAND, OPE_ARGUMENT, OPE_PIPE, OPE_AND,
		OPE_OR, OPE_PAREN, OPE_INPUT, OPE_HEREDOC, OPE_OUTPUT,
		OPE_OUTPUT_APPEND, OPE_SEMICOLON, OPE_UNKNOWN, OPE_END};

	return (symbol[type]);
}

// Function to select the type of operator
t_node_type	select_operator(t_token_type type)
{
	if (type == T_PIPE)
		return (NODE_PIPE);
	else if (type == T_AND)
		return (NODE_AND);
	else if (type == T_OR)
		return (NODE_OR);
	else if (type == T_SEMICOLON)
		return (NODE_SEMICOLON);
	else if (type == T_INPUT)
		return (NODE_INPUT);
	else if (type == T_HEREDOC)
		return (NODE_HEREDOC);
	else if (type == T_OUTPUT)
		return (NODE_OUTPUT);
	else if (type == T_OUTPUT_APPEND)
		return (NODE_OUTPUT_APPEND);
	else
		return (NODE_UNKNOWN);
}

// Function to find the main operator considering precedence and parentheses
int	find_operator(t_token **tokens, int num_tokens)
{
	int	depth;
	int	last_operator_index;
	int	i;

	depth = 0;
	last_operator_index = NOT_FOUND;
	i = -1;
	while (++i < num_tokens)
	{
		if (tokens[i]->type == T_PAREN_OPEN)
			depth++;
		else if (tokens[i]->type == T_PAREN_CLOSE)
			depth--;
		else if (depth == 0)
			if (tokens[i]->type == T_OR || tokens[i]->type == T_AND
				|| tokens[i]->type == T_SEMICOLON || tokens[i]->type == T_PIPE
				|| tokens[i]->type == T_INPUT || tokens[i]->type == T_HEREDOC
				|| tokens[i]->type == T_OUTPUT
				|| tokens[i]->type == T_OUTPUT_APPEND)
				last_operator_index = i;
	}
	if (depth < 0)
		return (ERROR);
	return (last_operator_index);
}

// AST Print function
void	print_ast(t_ast_node *root)
{
	int			i;
	const char	*messages[] = {M_COMMAND, M_ARGUMENT, M_PIPE, M_AND, M_OR,
		M_PAREN, M_INPUT, M_HEREDOC, M_OUTPUT, M_OUTPUT_APPEND, M_SEMICOLON,
		M_UNKNOWN};

	if (root == NULL)
		return ;
	i = -1;
	while (++i < root->level)
		printf("   ");
	printf("(%d) %s[%d]: %s (%lu)\n", root->level, messages[root->type],
		root->type, root->value, ft_strlen(root->value));
	print_ast(root->left);
	print_ast(root->right);
}
