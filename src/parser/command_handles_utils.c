#include "command.h"

void	delete_command(t_cmd **node)
{
	int		i;
	t_cmd	*next_node;

	if (*node == NULL)
		return ;
	next_node = (*node)->next;
	if ((*node)->name)
		ft_free_str((*node)->name);
	if ((*node)->arg)
	{
		i = -1;
		while (++i < (*node)->n_args)
		{
				ft_free_str((*node)->arg[i]);
		}
		free((*node)->arg);
	}
	free((*node));
	*node = next_node;
}

void	ft_free_str(char *str)
{
	if (!str)
		free(str);
	str = NULL;
}

char	*read_until_eof(char *line, char *eof)
{
	char			*input;
	char			*temp_input;
	unsigned long	i;

	i = 0;
	input = ft_strdup("");
	while (++i)
	{
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (line && ft_strcmp(line, eof) == OK)
			break ;
		if (line == NULL)
		{
			printf("minishell: warning: here-document at line %ld delimited by "
				"(wanted «%s»)\n", i, eof);
			break ;
		}
		temp_input = ft_strdup(input);
		ft_free_str(input);
		input = ft_strjoin(temp_input, line);
		ft_free_str(temp_input);
		ft_free_str(line);
	}
	return (input);
}

void	ft_read_stdin(int fd, char *eof, t_shell *data)
{
	char	*replace_input;
	char	*line;
	char	*input;

	line = NULL;
	input = read_until_eof(line, eof);
	ft_free_str(line);
	replace_input = replace_env_variables(input, data);
	ft_free_str(input);
	write(fd, replace_input, ft_strlen(replace_input));
	ft_free_str(replace_input);
}

t_cmd	*process_node_commands(t_cmd_arg *arg, t_shell *data, int fd,
		t_redirect dir)
{
	t_cmd		*head;
	t_cmd		*tail;
	t_cmd		*left_cmds;
	t_cmd		*right_cmds;
	t_ast_node	*node;

	head = NULL;
	tail = NULL;
	node = arg->node;
	arg->node = node->left;
	left_cmds = traverse_ast(arg, data);
	arg->node = node->right;
	right_cmds = traverse_ast(arg, data);
	arg->node = node;
	append_commands(&head, &tail, left_cmds);
	if (left_cmds)
	{
		if (dir == R_INFILE)
			tail->fdin = fd;
		else if (dir == R_OUTFILE)
			tail->fdout = fd;
	}
	append_commands(&head, &tail, right_cmds);
	return (head);
}
