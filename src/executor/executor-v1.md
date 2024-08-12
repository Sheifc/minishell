void set_pipes(t_cmd **cmd)
{
    t_cmd *current = *cmd;
    t_cmd *next;
    int fdpipe[2];

    while (current)
    {
        if (current->next)
        {
            next = current->next;
            if (pipe(fdpipe) < 0)
            {
                perror("Error: pipe failed");
                exit(EXIT_FAILURE);
            }
            if (current->fdout == -1)
                current->fdout = fdpipe[1];
            else
                close(fdpipe[1]);

            if (next->fdin == -1)
                next->fdin = fdpipe[0];
            else
                close(fdpipe[0]);
        }
        current = current->next;
    }
}

void	executor(t_shell *data)
{
	t_cmd	*current;

	count_commands(data);
	current = data->cmd;
	if (!current)
		return ;
	//print_commands(current);
	set_tmp_fds(data);
	if (data->cmd_count == 1)
		exec_one_cmd(data, current);
	else if (data->cmd_count > 1)
	{
		print_commands(current);
		//set_pipes(&current);
		//dprintf(2, "\nAfter Pipes set\n");
		//print_commands(current);
		exec_multiple_cmds(data, current);
	}
	restart_fds(data);
}

/* void	set_pipe(t_cmd *cmd)
{
	int fdpipe[2];

	if (pipe(fdpipe) < 0)
	{
		perror("Error: pipe failed");
		exit(EXIT_FAILURE);
	}
	if (cmd->fdout == -1)
		ft_memcpy(&(cmd->fdout), fdpipe + 1, sizeof(int));
	else
		close(fdpipe[1]);
	if (cmd->next)
	{
		//dprintf(2, "entra en set_pipe next\n");
		if (cmd->next->fdin == -1)
			ft_memcpy(&(cmd->next->fdin), fdpipe + 0, sizeof(int));
		else
			close(fdpipe[0]);
	}
} */