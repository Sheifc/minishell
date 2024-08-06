#include "minishell.h"

void	print_list(t_env *head)
{
	t_env	*current;

	current = head;
	while (current)
	{
		if (current->key && current->value)
			printf("%s=%s\n", current->key, current->value);
		else if (current->key)
			printf("%s=\n", current->key);
		else if (current->value)
			printf("=%s\n", current->value);
		current = current->next;
	}
}

void	print_key(t_env *head)
{
	t_env	*temp;

	temp = head;
	while (temp != NULL)
	{
		printf("%s\n", temp->key);
		temp = temp->next;
	}
}

char	*print_value(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strncmp(env->key, key, ft_strlen(env->key)+1) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	print_argu(char **args)
{
	int	i;

	i = 0;
	while (args[i] != NULL)
	{
		dprintf(2, "Arg[%d]: %s\n", i, args[i]);
		i++;
	}
}

void	print_cmd(t_cmd *cmd)
{
	int	i;

	printf(" Command: %s\n", cmd->name);
	i = -1;
	while (++i < cmd->n_args)
		printf("    Arg[%d]: %s\n", i, cmd->arg[i]);
	printf("fd_in: %d fd_out: %d\n", cmd->fdin,
		cmd->fdout);
	printf("  next_operator: %s [%d]\n", node_type_to_symbol(cmd->operator),
		cmd->operator);
}

void	print_cmds(t_cmd *cmd)
{
	t_cmd	*current;

	current = NULL;
	if (cmd)
	{
		printf("\n**** List of Commands: ****\n");
		current = cmd;
		while (current)
		{
			print_cmd(current);
			current = current->next;
		}
	}
}
