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
		close(cmd->input_fd);
		close(cmd->output_fd);
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

// Ejecuta los comandos conectados por tuberías
// int	execute_pipe(ASTNode *node)
// {
// 	int		pipefd[2];
// 	Command	*left_cmd;
// 	Command	*right_cmd;
// 	pid_t	pid1;
// 	pid_t	pid2;
// 	int		status;

// 	if (pipe(pipefd) == -1)
// 	{
// 		perror("pipe");
// 		return (-1);
// 	}
// 	left_cmd = create_command_from_ast(node->left);
// 	right_cmd = create_command_from_ast(node->right);
// 	left_cmd->output_fd = pipefd[WRITE];
// 	right_cmd->input_fd = pipefd[READ];
// 	pid1 = execute_command(left_cmd);
// 	if (pid1 == -1)
// 	{
// 		close(pipefd[READ]);
// 		close(pipefd[WRITE]);
// 		return (-1);
// 	}
// 	close(pipefd[WRITE]);
// 	pid2 = execute_command(right_cmd);
// 	if (pid2 == -1)
// 	{
// 		close(pipefd[READ]);
// 		return (-1);
// 	}
// 	close(pipefd[READ]);
// 	waitpid(pid1, &status, 0);
// 	waitpid(pid2, &status, 0);
// 	return (WEXITSTATUS(status));
// }