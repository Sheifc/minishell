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

	args = (char **)malloc((cmd->arg_count + 1) * sizeof(char *));
	i = -1;
	while (++i < cmd->arg_count)
		args[i] = cmd->args[i];
	args[cmd->arg_count] = (char *)malloc((ft_strlen(arg) + 1) * sizeof(char));
	ft_strlcpy(args[cmd->arg_count], arg, ft_strlen(arg) + 1);
	free(cmd->args);
	cmd->args = args;
	cmd->arg_count++;
}

// Función crear comando para execvp
char	**build_cmd_args(Command *cmd)
{
	int		i;
	char	**args;

	args = (char **)malloc((cmd->arg_count + 2) * sizeof(char *));
	args[0] = cmd->name;
	i = -1;
	while (++i < cmd->arg_count)
		args[i + 1] = cmd->args[i];
	args[cmd->arg_count + 1] = NULL;
	return (args);
}

// Función para liberar un comando
void	free_command(Command *cmd)
{
	int	i;

	if (cmd)
	{
		if (cmd->name)
			free(cmd->name);
		if (cmd->args)
		{
			i = -1;
			while (++i < cmd->arg_count)
			{
				if (cmd->args[i])
					free(cmd->args[i]);
			}
			free(cmd->args);
		}
		free(cmd);
	}
}

// Función para imprimir un nodo de comando (para debug)
void	print_command(Command *cmd)
{
	int	i;

	printf(" Command: %s\n", cmd->name);
	i = -1;
	while (++i < cmd->arg_count)
		printf("   Arg[%d]: %s\n", i, cmd->args[i]);
}
