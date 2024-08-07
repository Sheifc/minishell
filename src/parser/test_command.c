#include "command.h"

// void	execute_commands(t_cmd *commands)
// {
// 	t_cmd	*current;
// 	pid_t	pid;
// 	int		status;

// 	current = commands;
// 	while (current)
// 	{
// 		printf("\e[0m - Ejecutando comando: \e[33m%s\e[0m -\e[32m\n",
// 			current->name);
// 		if (current->operator == NODE_END && (ft_strncmp(current->name,
// 					"save_outfile", 12) == 0 || ft_strncmp(current->name,
// 					"save_append", 11) == 0))
// 		{
// 		}
// 		else
// 		{
// 			if (ft_strncmp(current->name, "read_infile", 11) == 0)
// 			{
// 				if (current->fdin != STDIN_FILENO)
// 				{
// 					close(current->fdin);
// 				}
// 				current = current->next;
// 				continue ;
// 			}
// 			if (ft_strncmp(current->name, "save_outfile", 12) == 0
// 				|| ft_strncmp(current->name, "save_append", 11) == 0)
// 			{
// 				current->name = ft_strdup("cat");
// 				current->arg[0] = ft_strdup("cat");
// 			}
// 			pid = fork();
// 			if (pid == 0)
// 			{
// 				// Child process
// 				if (current->fdin != STDIN_FILENO)
// 				{
// 					dup2(current->fdin, STDIN_FILENO);
// 					close(current->fdin);
// 				}
// 				if (current->fdout != STDOUT_FILENO)
// 				{
// 					dup2(current->fdout, STDOUT_FILENO);
// 					close(current->fdout);
// 				}
// 				execvp(current->name, current->arg);
// 				perror("execvp");
// 				exit(EXIT_FAILURE);
// 			}
// 			else if (pid < 0)
// 			{
// 				perror("fork");
// 				exit(EXIT_FAILURE);
// 			}
// 			// Parent process
// 			if (current->fdin != STDIN_FILENO)
// 			{
// 				close(current->fdin);
// 			}
// 			if (current->fdout != STDOUT_FILENO)
// 			{
// 				if (!current->next || current->next->fdout != current->fdout)
// 					close(current->fdout);
// 			}
// 			// Wait for the child process to finish
// 			waitpid(pid, &status, 0);
// 			printf("\e[0m");
// 			// Check if the command was executed successfully
// 			if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
// 			{
// 				fprintf(stderr, "t_cmd failed with status %d: %s\n",
// 					WEXITSTATUS(status), current->name);
// 			}
// 		}
// 		// Move to the next command
// 		current = current->next;
// 	}
// }

void	handle_child_process(t_cmd *current)
{
	if (current->fdin != STDIN_FILENO)
	{
		dup2(current->fdin, STDIN_FILENO);
		close(current->fdin);
	}
	if (current->fdout != STDOUT_FILENO)
	{
		dup2(current->fdout, STDOUT_FILENO);
		close(current->fdout);
	}
	execvp(current->name, current->arg);
	perror("execvp");
	exit(EXIT_FAILURE);
}

void	handle_parent_process2(t_cmd *current, pid_t pid)
{
	int	status;

	if (current->fdin != STDIN_FILENO)
		close(current->fdin);
	if (current->fdout != STDOUT_FILENO)
	{
		if (!current->next || current->next->fdout != current->fdout)
			close(current->fdout);
	}
	waitpid(pid, &status, 0);
	printf("\e[0m");
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		fprintf(stderr, "t_cmd failed with status %d: %s\n",
			WEXITSTATUS(status), current->name);
}

void	execute_command2(t_cmd *current)
{
	pid_t	pid;

	if (ft_strcmp(current->name, "read_infile") == 0)
	{
		if (current->fdin != STDIN_FILENO)
			close(current->fdin);
		current = current->next;
	}
	else
	{
		if (ft_strcmp(current->name, "save_outfile") == 0
			|| ft_strcmp(current->name, "save_append") == 0)
		{
			free(current->name);
			free(current->arg[0]);
			current->name = ft_strdup("cat");
			current->arg[0] = ft_strdup("cat");
		}
		pid = fork();
		if (pid == 0)
			handle_child_process(current);
		else if (pid < 0)
			exit(EXIT_FAILURE);
		else
			handle_parent_process2(current, pid);
	}
}

void	execute_commands(t_cmd *commands)
{
	t_cmd	*current;

	current = commands;
	while (current)
	{
		printf("\e[0m - Ejecutando comando: \e[33m%s\e[0m -\e[32m\n",
			current->name);
		if (current->operator == NODE_END && (ft_strncmp(current->name,
					"save_outfile", 12) == 0 || ft_strncmp(current->name,
					"save_append", 11) == 0))
		{
		}
		else
			execute_command2(current);
		current = current->next;
	}
}

int	main(void)
{
	t_shell		data;
	bool		is_valid;
	const char	*input = "ls >< ls";

	printf("\e[35m\n------------------- * -------------------\n\e[0m");
	printf("input:\n%s\n", input);
	data.prompt = (char *)input;
	data.num_tokens = 0;
	data.tokens = tokenize_input(&data);
	data.ast = create_ast(&data);
	is_valid = validate_and_free_tokens(&data);
	data.cmd = generate_commands(data.ast, is_valid, (Fds){STDIN_FILENO, STDOUT_FILENO});
	// printf("\n**** Ejecutando: ****\n");
	// execute_commands(data.cmd);
	free_commands(&data.cmd);
	return (0);
}

// input = "cat out1.txt | sort";
// input = "sort << EOF";
// input = "ls -l file*.txt ; ls -l *[1].txt";
// input = "sort < out1.txt";
// input = "(ls file*.txt | wc | wc && ls arch*.txt) > out1.txt >> out2.txt";
// input = "ls file*.txt > out1.txt > out2.txt";
// input = "\"e\"\"c\"\"h\"\"o\" hola"
// input = "cat /dev/random | head";
// input = "cat | cat | ls";
// input = "echo hola | cat > out1.txt";
// input = "echo hola | echo hola | echo bye";
// input = "ls -l file*.txt && ls -l arch*.txt > out1.txt";
// input = "ls -l file*.txt | wc > out1.txt >> out2.txt >> out3.txt";
// input = "((ls file* | wc) && (ls arch* | wc -l) && ls arch*.txt) | wc";
