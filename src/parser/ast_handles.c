/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_handles.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:45:31 by sheferna          #+#    #+#             */
/*   Updated: 2024/08/27 18:45:33 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

// Function to build the command node and its arguments
t_ast_node	*build_command_node(t_token **tokens, int num_tokens, int level)
{
	int			i;
	t_ast_node	*root;
	t_ast_node	*current;

	root = NULL;
	if (num_tokens > 0)
	{
		i = -1;
		while (++i < num_tokens && tokens[i]->type == T_QUOTE)
			;
		root = create_node(NODE_COMMAND, tokens[i]->value, level);
		current = root;
		while (++i < num_tokens)
		{
			if (tokens[i]->type == T_ARG || tokens[i]->type == T_TEXT
				|| tokens[i]->type == T_WILDCARD)
			{
				current->left = create_node(NODE_ARGUMENT, tokens[i]->value,
						level + 1);
				current = current->left;
			}
		}
	}
	return (root);
}

t_ast_node	*build_redirect_node(t_token **tokens, char *name, int num_tokens,
		int level)
{
	t_ast_node	*root;

	root = NULL;
	if (num_tokens > 0)
	{
		root = create_node(NODE_COMMAND, name, level);
		root->left = create_node(NODE_ARGUMENT, tokens[0]->value, level + 1);
	}
	return (root);
}

// Function to handle redirects
t_ast_node	*handle_operators(t_token **tokens, int num_tokens, int level,
		int *pos)
{
	t_token_type	op_type;
	t_ast_node		*root;

	*pos = find_operator(tokens, num_tokens);
	if (*pos == ERROR)
	{
		ft_error(E_SYNTAX, "A parenthesis has not been opened/closed", NULL);
		return (NULL);
	}
	if (*pos != NOT_FOUND)
	{
		op_type = tokens[*pos]->type;
		root = create_node(select_operator(op_type), tokens[*pos]->value,
				level);
		root->left = build_ast(tokens, *pos, level + 1);
		root->right = build_ast(tokens + *pos + 1, num_tokens - *pos - 1, level
				+ 1);
		return (root);
	}
	return (NULL);
}

// Function to handle parentheses
t_ast_node	*handle_parentheses(t_token **tokens, int num_tokens, int level)
{
	t_ast_node	*root;
	int			close_pos;

	close_pos = find_matching_paren(tokens, 0, num_tokens);
	if (close_pos == NOT_FOUND)
	{
		ft_error(E_SYNTAX, "A parenthesis has not been closed", NULL);
		return (NULL);
	}
	root = create_node(NODE_PARENTHESIS, "()", level);
	root->right = NULL;
	root->left = build_ast(tokens + 1, close_pos - 1, level + 1);
	return (root);
}

// Function to handle redirects
t_ast_node	*handle_redirection(t_token **tokens, int num_tokens, int level)
{
	int	i;

	i = -1;
	if (num_tokens > 0)
	{
		while (++i < num_tokens && tokens[i]->type == T_QUOTE)
			;
		if (tokens[i]->type == T_REDIRECT_ARG)
		{
			if ((tokens - 1)[0]->type == T_OUTPUT)
				return (build_redirect_node(&tokens[i], "save_outfile",
						num_tokens, level));
			if ((tokens - 1)[0]->type == T_OUTPUT_APPEND)
				return (build_redirect_node(&tokens[i], "save_append",
						num_tokens, level));
			if ((tokens - 1)[0]->type == T_INPUT)
				return (build_redirect_node(&tokens[i], "read_infile",
						num_tokens, level));
			if ((tokens - 1)[0]->type == T_HEREDOC)
				return (build_redirect_node(&tokens[i], "heredoc", num_tokens,
						level));
			return (build_redirect_node(&tokens[i], "cat", num_tokens, level));
		}
	}
	return (NULL);
}
