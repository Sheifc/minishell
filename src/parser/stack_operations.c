/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:47:14 by sheferna          #+#    #+#             */
/*   Updated: 2024/08/27 18:47:15 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stacks.h"

void	print_ope_stack(t_operator_stack *head)
{
	t_operator_stack	*current;

	current = head;
	printf("Operation stack:\n");
	while (current)
	{
		printf("  - type: %s\n", node_type_to_symbol(current->type));
		current = current->next;
	}
}

void	push_operator(t_operator_stack **stack, t_node_type type)
{
	t_operator_stack	*new_node;

	new_node = (t_operator_stack *)malloc(sizeof(t_operator_stack));
	if (!new_node)
	{
		ft_error(E_MEMORY, NULL, NULL);
		return ;
	}
	new_node->type = type;
	new_node->next = *stack;
	*stack = new_node;
}

t_node_type	pop_operator(t_operator_stack **stack)
{
	t_operator_stack	*top;
	t_node_type			type;

	if (*stack == NULL)
		return (NODE_END);
	top = *stack;
	type = top->type;
	*stack = top->next;
	free(top);
	return (type);
}

t_node_type	peek_operator(t_operator_stack *stack)
{
	if (stack == NULL)
		return (NODE_END);
	return (stack->type);
}

t_node_type	count_operator(t_operator_stack *head, t_node_type type)
{
	int					count;
	t_operator_stack	*current;

	count = 0;
	current = head;
	while (current)
	{
		if (current->type == type)
			count++;
		current = current->next;
	}
	return (count);
}
