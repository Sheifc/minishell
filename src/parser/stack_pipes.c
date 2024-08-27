/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:47:19 by sheferna          #+#    #+#             */
/*   Updated: 2024/08/27 18:47:20 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stacks.h"

void	print_pipe_stack(t_pipe_stack *head)
{
	t_pipe_stack	*current;

	current = head;
	printf("Pipe stack:\n");
	while (current)
	{
		printf("  - fd_in:%d, fd_out:%d\n", current->fdin, current->fdout);
		current = current->next;
	}
}

void	push_pipe(t_pipe_stack **stack, int fdin, int fdout)
{
	t_pipe_stack	*new_node;

	new_node = (t_pipe_stack *)malloc(sizeof(t_pipe_stack));
	if (!new_node)
	{
		ft_error(E_MEMORY, NULL, NULL);
		return ;
	}
	new_node->fdin = fdin;
	new_node->fdout = fdout;
	new_node->next = *stack;
	*stack = new_node;
}

t_pipe_stack	*pop_pipe(t_pipe_stack **stack)
{
	t_pipe_stack	*top;

	if (*stack == NULL)
		return (NULL);
	top = *stack;
	*stack = top->next;
	free(top);
	return (*stack);
}

t_pipe_stack	*peek_pipe(t_pipe_stack *stack)
{
	if (stack == NULL)
		return (NULL);
	return (stack);
}
