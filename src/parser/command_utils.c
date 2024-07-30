#include "command.h"

// Función que imprime el contenido dentro de un fd
void	print_fd_contents(int fd)
{
	char	buffer[CMD_BUFFER_SIZE];
	ssize_t	bytes_read;

	bytes_read = read(fd, buffer, sizeof(buffer) - 1);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		printf("\e[32m%s\e[0m", buffer);
		bytes_read = read(fd, buffer, sizeof(buffer) - 1);
	}
	if (bytes_read == -1)
	{
		perror("read");
	}
}

// Función para agregar un argumento al nodo de comando
void	add_argument(Command *cmd, const char *arg)
{
	int		i;
	char	**args;

	args = (char **)malloc((cmd->n_args + 2) * sizeof(char *));
	i = -1;
	while (++i < cmd->n_args)
		args[i] = cmd->arg[i];
	args[cmd->n_args] = (char *)malloc((ft_strlen(arg) + 1) * sizeof(char));
	ft_strlcpy(args[cmd->n_args], arg, ft_strlen(arg) + 1);
	free(cmd->arg);
	cmd->arg = args;
	args[cmd->n_args + 1] = NULL;
	cmd->n_args++;
}

// Función crear comando para execvp
char	**build_cmd_args(Command *cmd)
{
	int		i;
	char	**args;

	args = (char **)malloc((cmd->n_args + 2) * sizeof(char *));
	args[0] = cmd->name;
	i = -1;
	while (++i < cmd->n_args)
		args[i + 1] = cmd->arg[i];
	args[cmd->n_args + 1] = NULL;
	return (args);
}

// Función para liberar un comando
void	free_commands(Command **head)
{
	int		i;
	Command	*next_node;

	if (*head == NULL)
		return ;
	next_node = (*head)->next;
	if (*head)
	{
		if ((*head)->name)
			free((*head)->name);
		if ((*head)->arg)
		{
			i = -1;
			while (++i < (*head)->n_args)
			{
				if ((*head)->arg[i])
					free((*head)->arg[i]);
			}
			free((*head)->arg);
		}
		free((*head));
	}
	*head = NULL;
	free_commands(&next_node);
}

// Función para imprimir un nodo de comando (para debug)
void	print_command(Command *cmd)
{
	int	i;

	printf(" Command: \e[33m%s\e[0m\n", cmd->name);
	i = -1;
	while (++i < cmd->n_args)
		printf("    Arg[%d]: %s\n", i, cmd->arg[i]);
	printf("  \e[34mfd_in: %d\e[0m, \e[35mfd_out: %d\e[0m\n", cmd->fdin,
		cmd->fdout);
	printf("  next_operator: %s [%d]\n", node_type_to_symbol(cmd->operator),
		cmd->operator);
}
