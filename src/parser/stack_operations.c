#include "stacks.h"

void	print_ope_stack(OperatorStack *head)
{
	OperatorStack	*current;

	current = head;
	printf("Operation stack:\n");
	while (current)
	{
		printf("  - type: %s\n", node_type_to_symbol(current->type));
		current = current->next;
	}
}

void	push_operator(OperatorStack **stack, NodeType type)
{
	OperatorStack	*new_node;

	new_node = (OperatorStack *)malloc(sizeof(OperatorStack));
	new_node->type = type;
	new_node->next = *stack;
	*stack = new_node;
}

NodeType	pop_operator(OperatorStack **stack)
{
	OperatorStack	*top;
	NodeType		type;

	if (*stack == NULL)
		return (NODE_END);
	top = *stack;
	type = top->type;
	*stack = top->next;
	free(top);
	return (type);
}

NodeType	peek_operator(OperatorStack *stack)
{
	if (stack == NULL)
		return (NODE_END);
	return (stack->type);
}
