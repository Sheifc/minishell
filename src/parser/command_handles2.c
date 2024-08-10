#include "command.h"

// Función para crear un nodo de comando
t_cmd	*create_command(const char *name, Fds fds, NodeType ope, int *status)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
	{
		ft_error(E_MEMORY, NULL, status);
		return (NULL);
	}
	cmd->name = ft_strdup(name);
	cmd->arg = NULL;
	cmd->n_args = 0;
	cmd->fdin = fds.in;
	cmd->fdout = fds.out;
	cmd->operator = ope;
	cmd->next = NULL;
	cmd->redirect = R_NONE;
	add_argument(cmd, name);
	return (cmd);
}

t_cmd	*create_command_from_ast(t_cmd_arg *arg, int *status, NodeType ope)
{
	t_cmd	*cmd;
	ASTNode	*arg_node;

	cmd = create_command(arg->node->value, arg->fds, ope, status);
	arg_node = arg->node->left;
	while (arg_node)
	{
		if (arg_node->type == NODE_ARGUMENT)
			add_argument(cmd, arg_node->value);
		arg_node = arg_node->left;
	}
	return (cmd);
}

void	append_commands(t_cmd **head, t_cmd **tail, t_cmd *new_cmds)
{
	if (new_cmds)
	{
		if (*head == NULL)
		{
			*head = new_cmds;
			*tail = new_cmds;
		}
		else
		{
			(*tail)->next = new_cmds;
			//new_cmds->prev = *tail;
		}
		while ((*tail)->next)
		{
			*tail = (*tail)->next;
		}
	}
}

t_cmd	*handle_node_and_or_semicolon(t_cmd_arg *arg, int *status)
{
	t_cmd	*head;
	t_cmd	*tail;
	t_cmd	*left_cmds;
	t_cmd	*right_cmds;
	ASTNode	*node;

	node = arg->node;
	push_operator(arg->ope_stack, arg->node->type);
	head = NULL;
	tail = NULL;
	arg->node = node->left;
	left_cmds = traverse_ast(arg, status);
	arg->node = node->right;
	right_cmds = traverse_ast(arg, status);
	arg->node = node;
	append_commands(&head, &tail, left_cmds);
	append_commands(&head, &tail, right_cmds);
	return (head);
}

t_cmd	*handle_node_parenthesis(t_cmd_arg *arg, int *status)
{
	NodeType	parent_ope;
	t_cmd		*head;
	t_cmd		*tail;
	t_cmd		*left_cmds;
	ASTNode		*node;

	parent_ope = peek_operator(*arg->ope_stack);
	if (parent_ope == NODE_OUTPUT || parent_ope == NODE_OUTPUT_APPEND)
	{
		arg->fds.out = peek_pipe(*arg->pipe_stack)->fdout;
		pop_pipe(arg->pipe_stack);
	}
	push_operator(arg->ope_stack, arg->node->type);
	head = NULL;
	tail = NULL;
	node = arg->node;
	arg->node = node->left;
	left_cmds = traverse_ast(arg, status);
	arg->node = node;
	append_commands(&head, &tail, left_cmds);
	return (head);
}
