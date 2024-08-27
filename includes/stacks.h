/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stacks.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:50:36 by sheferna          #+#    #+#             */
/*   Updated: 2024/08/27 18:50:37 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACKS_H
# define STACKS_H

# include "ast.h"

typedef struct s_operator_stack
{
	t_node_type				type;
	struct s_operator_stack	*next;
}							t_operator_stack;

typedef struct s_pipe_stack
{
	int						fdin;
	int						fdout;
	struct s_pipe_stack		*next;
}							t_pipe_stack;

// Stack_operation
void						print_ope_stack(t_operator_stack *head);
void						push_operator(t_operator_stack **stack,
								t_node_type type);
t_node_type					pop_operator(t_operator_stack **stack);
t_node_type					peek_operator(t_operator_stack *stack);
t_node_type					count_operator(t_operator_stack *head,
								t_node_type type);

// Stack_pipe
void						print_pipe_stack(t_pipe_stack *head);
void						push_pipe(t_pipe_stack **stack, int fdin,
								int fdout);
t_pipe_stack				*pop_pipe(t_pipe_stack **stack);
t_pipe_stack				*peek_pipe(t_pipe_stack *stack);

#endif