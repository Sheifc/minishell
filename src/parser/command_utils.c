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
void	free_command(Command *cmd)
{
	int	i;

	if (cmd)
	{
		if (cmd->name)
			free(cmd->name);
		if (cmd->arg)
		{
			i = -1;
			while (++i < cmd->n_args)
			{
				if (cmd->arg[i])
					free(cmd->arg[i]);
			}
			free(cmd->arg);
		}
		free(cmd);
	}
}

char *nodeTypeToSymbol(NodeType type)
{
    switch (type)
    {
        case NODE_COMMAND:
            return "COMMAND";
        case NODE_ARGUMENT:
            return "ARGUMENT";
        case NODE_PIPE:
            return "|";
        case NODE_AND:
            return "&&";
        case NODE_OR:
            return "||";
        case NODE_PARENTHESIS:
            return "()";
        case NODE_TEXT:
            return "TEXT";
        case NODE_INPUT:
            return "<";
        case NODE_HEREDOC:
            return "<<";
        case NODE_OUTPUT:
            return ">";
        case NODE_OUTPUT_APPEND:
            return ">>";
        case NODE_SEMICOLON:
            return ";";
        case NODE_UNKNOWN:
            return "UNKNOWN";
        case NODE_END:
            return "END";
        default:
            return "UNDEFINED";
    }
}

// Función para imprimir un nodo de comando (para debug)
void	print_command(Command *cmd)
{
	int	i;

	printf(" Command: \e[33m%s\e[0m\n", cmd->name);
	i = -1;
	while (++i < cmd->n_args)
		printf("    Arg[%d]: %s\n", i, cmd->arg[i]);
	printf("  \e[34mfd_in: %d\e[0m, \e[35mfd_out: %d\e[0m\n", cmd->fdin, cmd->fdout);
	printf("  next_operator: %s [%d]\n", nodeTypeToSymbol(cmd->operator), cmd->operator);
}
