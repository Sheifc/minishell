#ifndef STACKS_H
# define STACKS_H

# include "ast.h"

typedef struct _OperatorStack
{
	NodeType				type;
	struct _OperatorStack	*next;
}							OperatorStack;

typedef struct _PipeStack
{
	int						fdin;
	int						fdout;
	struct _PipeStack		*next;
}							PipeStack;

// Stack_operation
void						print_ope_stack(OperatorStack *head);
void						push_operator(OperatorStack **stack, NodeType type);
NodeType					pop_operator(OperatorStack **stack);
NodeType					peek_operator(OperatorStack *stack);
NodeType					count_operator(OperatorStack *head, NodeType type);

// Stack_pipe
void						print_pipe_stack(PipeStack *head);
void						push_pipe(PipeStack **stack, int fdin, int fdout);
PipeStack					*pop_pipe(PipeStack **stack);
PipeStack					*peek_pipe(PipeStack *stack);

#endif