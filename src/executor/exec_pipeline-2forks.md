#include "minishell.h"

static void	save_close(int fd)
{
	//dprintf(2,"\nClosing fd: %d\n", fd);  // Depuración
	if (fd > 0)
		close(fd);
}

static void	iterate_to_close(t_cmd *current, t_cmd *next, t_cmd **cmds)
{
	t_cmd *cmd_iter = *cmds;

    while (cmd_iter)
    {
        if (cmd_iter == current){
			dprintf(2, "\nif\n");
			dprintf(2, "Closing fdin: %d\n", cmd_iter->fdin);  // Depuración
            save_close(cmd_iter->fdin);}
        else if (next && cmd_iter == next){
			dprintf(2, "\nelse if\n");
			dprintf(2, "Closing fdout: %d\n", cmd_iter->fdout);  // Depuración
            save_close(cmd_iter->fdout);}
        else
        {
			dprintf(2, "\nelse\n");  // Depuración
			dprintf(2, "Closing fdin: %d\n", cmd_iter->fdin);  // Depuración
            save_close(cmd_iter->fdin);
			dprintf(2, "Closing fdout: %d\n", cmd_iter->fdout);  // Depuración
            save_close(cmd_iter->fdout);
        }
        cmd_iter = cmd_iter->next;
    }
}

void	close_pipe(t_shell *data, t_cmd *cmd)
{
	t_cmd	*current;
	t_cmd	*next;

	next = NULL;
	current = NULL;
	if (cmd)
		current = cmd;
	if (cmd && cmd->next)
		next = cmd->next;
	iterate_to_close(current, next, &(data->cmd));
}

//execute generic: previamente se habia ejecutado los builtins
//y se crea otro hijo para ejecutar los comandos que no son builtins 
//en otra funcion llamada execaux
int	run_cmd(t_shell *data, t_cmd *cmd)
{
	if (!execute_builtin(data, cmd, cmd->arg[0]))
	{
		pid_t grandchild_pid = fork();
		if (grandchild_pid < 0)
		{
			perror("Error: fork failed");
			return (errno);
		}
		if (grandchild_pid == 0)
		{
			dprintf(2, "\nExecuting command: %s\n", cmd->arg[0]);
			get_path(data, cmd);
			if (!data->path)
			{
				perror("Error: command not found");
				return(127);
			}
			if (execve(data->path, cmd->arg, data->envp) < 0)
			{
				perror("Error: execve failed");
				return(errno);
			}
		}
		else
		{
			dprintf(2, "\nWaiting for grandchild process\n");  // Depuración
			waitpid(grandchild_pid, NULL, 0);
		}
	}
	return (0);
}

pid_t	save_fork(t_shell *data)
{
	data->pid = fork();
	if (data->pid == -1)
	{
		perror("Error: fork failed");
		exit(1);
	}
	return (data->pid);
}

void	save_closes(t_cmd *cmd)
{
	if (cmd->fdin != -1 && cmd->fdin != 0)
		close(cmd->fdin);
	if (cmd->fdout != -1 && cmd->fdout != 1)
		close(cmd->fdout);
}
//execute: donde se setean los dup2 de archivos
//cierre de pipes
//llamar a run_cmd
//cierre de fds
int	exec_process(t_shell *data, t_cmd **cmds)
{
	int status = 0;

	t_cmd *cmd = *cmds;
	if (!cmd->arg || !cmd->arg[0])
        return (1);
	
	//close_pipe(data, cmd);
	status = run_cmd(data, cmd);
	dprintf(2, "\nvuelve de run_cmd estamos en proceso hijo\n");  // Depuración
	//close_pipe(data, cmd);
/* 	if (cmd->fdout > 0)
        close(cmd->fdout);
    if (cmd->next)
        close(cmd->next->fdin); */
	if (cmd->fdout > 0)
	{
		close(cmd->fdout);
		dprintf(2, "Closed fdout en el hijo: %d\n", cmd->fdout);  // Depuración
	}
	if (cmd->fdin > 0){
        close(cmd->fdin);
		dprintf(2, "Closed fdin en el hijo: %d\n", cmd->fdin);}
/* 	if (cmd->next && cmd->next->fdin > 0)
	{
		close(cmd->next->fdin);
		dprintf(2, "Closed next fdin: %d\n", cmd->next->fdin);  // Depuración
	} */
/* 	if (cmd->fdin > 0)
        dup2(data->tmpin, STDIN_FILENO);
    if (cmd->fdout > 0)
        dup2(data->tmpout, STDOUT_FILENO); */
/* 	if (cmd->fdin > 0)
	{
		printf("Restoring stdin from %d to %d\n", cmd->fdin, data->tmpin);  // Depuración
		dup2(data->tmpin, STDIN_FILENO);
	}
	if (cmd->fdout > 0)
	{
		printf("Restoring stdout from %d to %d\n", cmd->fdout, data->tmpout);  // Depuración
		dup2(data->tmpout, STDOUT_FILENO);
	} */

	return(status);
}

void	redirect_files(t_cmd * cmd)
{
 	if (cmd->fdin != -1 && cmd->fdin != 0)
	{
		dprintf(2, "entra en infile\n");
		if (dup2(cmd->fdin, 0) == -1)
		{
			perror("Error: dup2 failed for cmd->fdin");
			exit(1);
		}
	}
 	if (cmd->fdout != -1 && cmd->fdout != 1)
	{
		dprintf(2, "entra en outfile\n");
		if (dup2(cmd->fdout, 1) == -1)
		{
			perror("Error: dup2 failed for cmd->fdout");
			exit(1);
		}
	}
}

//execute_pipe: en un hijo se llama a execute con exit: exit(execute(&cmds, data));
//cmds = data->cmd;
/* int	exec_pipe(t_shell *data, t_cmd *cmd) 
{
	int	status;
	
	status = 0;
	if (save_fork(data) == 0)
	{
		dprintf(2, "\nChild process: fdin = %d, fdout = %d\n", cmd->fdin, cmd->fdout);

		redirect_files(cmd);
		status = exec_process(data, &cmd);
		if (cmd->fdin > 0)
        {
            close(cmd->fdin);
            dprintf(2, "Closed fdin en el hijo: %d\n", cmd->fdin);
        }
        if (cmd->fdout > 0)
        {
            close(cmd->fdout);
            dprintf(2, "Closed fdout en el hijo: %d\n", cmd->fdout);
        }
		exit(status);
	}
	else
	{
		dprintf(2, "\nParent process: fdin = %d, fdout = %d\n", cmd->fdin, cmd->fdout);  // Depuración
    	//close_pipe(data, cmd);
		if (cmd->fdout > 0)
		{
			close(cmd->fdout);
			dprintf(2, "Closed fdout en el padre: %d\n", cmd->fdout);  // Depuración
		}
		if (cmd->fdin > 0){
			close(cmd->fdin);
			dprintf(2, "Closed fdin en el padre: %d\n", cmd->fdin);}
		wait_process(data);
		if (cmd->next)
			exec_multiple_cmds(data, cmd->next);
	}
	return (status);
}
 */
/* int exec_pipe(t_shell *data, t_cmd *cmd) 
{
    int pipefd[2];

    if (pipe(pipefd) == -1)
    {
        perror("Error: pipe failed");
        exit(EXIT_FAILURE);
    }

    data->pid = fork();
    if (data->pid == -1)
    {
        perror("Error: fork failed");
        exit(EXIT_FAILURE);
    }

    if (data->pid == 0)  // Proceso hijo - ejecuta `cat`
    {
        close(pipefd[0]);  // Cierra el extremo de lectura del pipe
        dup2(pipefd[1], STDOUT_FILENO);  // Redirige stdout al extremo de escritura del pipe
        close(pipefd[1]);  // Cierra el extremo de escritura original

        redirect_files(cmd);
        exec_process(data, &cmd);
        exit(EXIT_SUCCESS);
    }
    else  // Proceso padre - ejecuta `ls`
    {
        close(pipefd[1]);  // Cierra el extremo de escritura del pipe
        dup2(pipefd[0], STDIN_FILENO);  // Redirige stdin al extremo de lectura del pipe
        close(pipefd[0]);  // Cierra el extremo de lectura original

        if (cmd->next)  // Ejecuta `ls`
            exec_multiple_cmds(data, cmd->next);

        wait_process(data);
    }
    return data->status;
} */

void	exec_redir(t_shell *data, t_cmd *cmd)
{
	//dprintf(2, "entra en redir\n");
	if (save_fork(data) == 0)
	{
		redir_from_infile_if_needed(cmd);
		redir_to_outfile_if_needed(cmd);
		run_cmd(data, cmd);
		exit(0);
	}
	wait_process(data);
	close(cmd->fdin);
	close(cmd->fdout);
	if (cmd->next)
		exec_multiple_cmds(data, cmd->next);
}

/* void exec_multiple_cmds(t_shell *data, t_cmd *cmd)
{
	//dprintf(2, "entra en multiple cmds\n");
	if (!cmd)
		return ;
	if (cmd->operator == NODE_OR || cmd->operator == NODE_AND)
		exec_bonus(data, cmd);
    else if (cmd->redirect == R_OUTFILE)
		exec_redir(data, cmd);
	else if (cmd->operator == NODE_PIPE || cmd->operator == NODE_END)
	{
		exec_pipe(data, cmd);
		//close_pipe(data, cmd);
	}
} */