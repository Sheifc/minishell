
#include "minishell.h"

static void	close_fd(int fd)
{
	if (fd > 0)
		close(fd);
}

static void	iterate_to_close(t_cmd *current, t_cmd *next, t_cmd *commands)
{
	while (commands)
	{
		if (commands == current)
			close_fd(commands->fdin);
		else if (next && commands == next)
			close_fd(commands->fdout);
		else
		{
			close_fd(commands->fdin);
			close_fd(commands->fdout);
		}
		commands = commands->next;
	}
}

void	close_pipes(t_shell *data, t_cmd *cmd)
{
	t_cmd	*current;
	t_cmd	*next;
	t_cmd	*commands;

	commands = data->cmd;
	next = NULL;
	current = NULL;
	if (cmd)
		current = cmd;
	if (cmd && cmd->next)
		next = cmd->next;
	iterate_to_close(current, next, commands);
}

int	is_builtin(char *command)
{
	return (ft_strncmp(command, "cd", 3) == 0
		|| ft_strncmp(command, "env", 4) == 0
		|| ft_strncmp(command, "export", 7) == 0
		|| ft_strncmp(command, "unset", 6) == 0
		|| ft_strncmp(command, "exit", 5) == 0
		|| ft_strncmp(command, "echo", 5) == 0);
}

int	execute_builtins(t_shell *data, t_cmd *command)
{
	if (ft_strncmp(command->arg[0], "cd\0", 3) == 0)
		ft_cd(data, command);
	else if (ft_strncmp(command->arg[0], "env\0", 4) == 0)
		ft_env(data, data->env);
	else if (ft_strncmp(command->arg[0], "export\0", 7) == 0)
		ft_export(data, command);
	else if (ft_strncmp(command->arg[0], "unset\0", 6) == 0)
		ft_unset(data);
	else if (ft_strncmp(command->arg[0], "exit\0", 5) == 0)
		ft_exit(command);
	else if (ft_strncmp(command->arg[0], "echo\0", 5) == 0)
		ft_echo(data, command);
	return (data->status);
}

int decode_error(int status, t_shell *data)
{
    int result = 1;

    if (WIFEXITED(status))  // Verifica si el proceso terminó normalmente
    {
        result = WEXITSTATUS(status);  // Obtén el código de salida del proceso
    }
    else if (WIFSIGNALED(status))  // Verifica si el proceso fue terminado por una señal
    {
        result = 128 + WTERMSIG(status);  // Retorna 128 + número de señal para los procesos terminados por una señal
    }
	data->status = result;
    return result;
}

void	free_ptr(void *ptr)
{
	if (ptr)
		free(ptr);
}

char	*join_strs(char *str, char *add)
{
	char	*tmp;

	if (!add)
		return (str);
	if (!str)
		return (ft_strdup(add));
	tmp = str;
	str = ft_strjoin(tmp, add);
	free_ptr(tmp);
	return (str);
}

static int	add_detail_quotes(char *command)
{
	return (ft_strncmp(command, "export", 7) == 0
		|| ft_strncmp(command, "unset", 6) == 0);
}

int	print_error(char *command, char *detail, char *error_message, int err)
{
	char	*msg;
	int		detail_quotes;

	detail_quotes = add_detail_quotes(command);
	msg = ft_strdup("minishell: ");
	if (command != NULL)
	{
		msg = join_strs(msg, command);
		msg = join_strs(msg, ": ");
	}
	if (detail != NULL)
	{
		if (detail_quotes)
			msg = join_strs(msg, "`");
		msg = join_strs(msg, detail);
		if (detail_quotes)
			msg = join_strs(msg, "'");
		msg = join_strs(msg, ": ");
	}
	msg = join_strs(msg, error_message);
	ft_putendl_fd(msg, STDERR_FILENO);
	free_ptr(msg);
	return (err);
}

int execaux(t_cmd *cmd, t_shell *data)
{
	get_path(data, cmd);
	if (!data->path)
	{
		perror("Error: command not found");
		return 127;  // Comando no encontrado
	}
	// Intentar ejecutar el comando
	if (execve(data->path, cmd->arg, data->envp) < 0)
	{
		perror("Error: execve failed");
		return errno;  // Fallo en execve
	}

	return 0;  // Éxito (aunque este punto no se alcanzará si execve es exitoso)
}

int execute_generic(t_cmd *cmd, t_shell *data)
{
    int result_code = 0;

    data->pid = fork();  // Crear un proceso hijo y guardar su PID en data->pid
    if (data->pid < 0)
    {
        perror("Error: fork failed");
        return data->pid;  // Retornar el código de error si fork falla
    }

    if (data->pid == 0)  // Proceso hijo
    {
        result_code = execaux(cmd, data);  // Ejecutar el comando en el proceso hijo
        exit(result_code);  // Salir con el código de retorno de execaux
    }

    // Proceso padre espera al proceso hijo
    waitpid(data->pid, &result_code, 0);  
    result_code = decode_error(result_code, data);  // Decodificar el estado de salida
    // Manejo del caso en que el comando no se encuentra
    if (result_code == 127)
    {
        print_error(cmd->arg[0], 0, "command not found", result_code);
    }
    return result_code;  // Retornar el código de resultado
}


int execute(t_cmd **cmds, t_shell *data)
{
    int status;
    t_cmd *command;

    command = *cmds;  // Apuntamos al primer comando en la lista
    if (!command->arg || !command->arg[0])
        return (0);
    
    // Redirigir la entrada y salida si están configurados
    if (command->fdin > 0)
        dup2(command->fdin, STDIN_FILENO);
    if (command->fdout > 0)
        dup2(command->fdout, STDOUT_FILENO);
    
    close_pipes(data, command);  // Cerrar pipes innecesarios
    
    // Ejecutar el comando
    if (is_builtin(command->arg[0]))
        status = execute_builtins(data, command);
    else
        status = execute_generic(command, data);
    
    // Cerrar descriptores de archivo después de la ejecución
	/*if (command->fdin > 0) // este no estaba
		close(command->fdin);*/
    if (command->fdout > 0)
        close(command->fdout);
    if (command->next)
        close(command->next->fdin);
	if (command->fdin > 0)
        dup2(data->tmpin, STDIN_FILENO);
    if (command->fdout > 0)
        dup2(data->tmpout, STDOUT_FILENO);
    return (status);
}

void set_pipes(t_shell *data)
{
	t_cmd *cmd;
	t_cmd *next;
	int pipes[2];

	t_cmd *instr = data->cmd;

	while (instr)
	{
		cmd = instr;
		if (instr->next)
		{
			next = instr->next;
			if (pipe(pipes) < 0)
			{
				perror("Error: pipe failed");
				exit(EXIT_FAILURE);
			}
			if (cmd->fdout == -1)  // Si fdout no está configurado, asignar extremo de escritura del pipe
				ft_memcpy(&(cmd->fdout), pipes + 1, sizeof(int));
			else
				close(pipes[1]);  // Si fdout ya está configurado, cerrar extremo de escritura

			if (next->fdin == -1)  // Si fdin no está configurado, asignar extremo de lectura del pipe
				ft_memcpy(&(next->fdin), pipes + 0, sizeof(int));
			else
				close(pipes[0]);  // Si fdin ya está configurado, cerrar extremo de lectura
		}
		instr = instr->next;
	}
}

int	execute_pipex(t_shell *data)
{
	int		status;
	int		last_pid;
	int		last_status;
	t_cmd	*commands;

	set_pipes(data);
	commands = data->cmd;
	while (commands)
	{
		last_pid = fork();
		if (last_pid < 0)
			return (last_pid);
		if (last_pid == 0)
			exit(execute(&commands, data));
		commands = commands->next;
	}
	commands = data->cmd;
	close_pipes(data, 0);
	commands = data->cmd;
	while (commands)
	{
		if (last_pid == waitpid(-1, &status, 0))
			last_status = decode_error(status, data);
		commands = commands->next;
	}
	return (last_status);
}

void exec_multiple_cmds(t_shell *data, t_cmd *cmd)
{
	if (cmd->operator == NODE_OR || cmd->operator == NODE_AND)
		exec_bonus(data, cmd);
	else if (cmd->operator == NODE_PIPE || cmd->operator == NODE_END)
		execute_pipex(data);
}
