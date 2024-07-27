#include "stacks.h"

void	print_pipe_stack(PipeStack *head)
{
	PipeStack	*current;

	current = head;
	printf("Pipe stack:\n");
	while (current)
	{
		printf("  - fd_in:%d, fd_out:%d\n", current->fdin, current->fdout);
		current = current->next;
	}
}

void	push_pipe(PipeStack **stack, int fdin, int fdout)
{
	PipeStack	*new_node;

	new_node = (PipeStack *)malloc(sizeof(PipeStack));
	new_node->fdin = fdin;
	new_node->fdout = fdout;
	new_node->next = *stack;
	*stack = new_node;
}

PipeStack	*pop_pipe(PipeStack **stack)
{
	PipeStack	*top;

	if (*stack == NULL)
		return (NULL);
	top = *stack;
	*stack = top->next;
	free(top);
	return (*stack);
}

PipeStack	*peek_pipe(PipeStack *stack)
{
	if (stack == NULL)
		return (NULL);
	return (stack);
}
