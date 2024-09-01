/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 10:32:15 by svilla-d          #+#    #+#             */
/*   Updated: 2024/09/01 10:32:16 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

// Ejecución de comando
// int	execute_command(t_cmd *cmd, int input_fd, int output_fd)
// {
// 	int		pipe_fds[2];
// 	pid_t	pid;
// 	int		status;

// 	printf(" - Ejecutando comando: \e[33m%s\e[0m -\n", cmd->name);
// 	if (pipe(pipe_fds) == -1)
// 	{
// 		perror("pipe");
// 		return (-1);
// 	}
// 	pid = create_child_process();
// 	if (pid == 0)
// 		setup_child_process(cmd, input_fd, output_fd, pipe_fds);
// 	else if (pid < 0)
// 		return (-1);
// 	handle_parent_process(pid, pipe_fds, &status);
// 	printf(" ------------------------------\n");
// 	if (WIFEXITED(status))
// 		return (WEXITSTATUS(status));
// 	return (-1);
// }

// pid_t	create_child_process(void)
// {
// 	pid_t	pid;

// 	pid = fork();
// 	if (pid < 0)
// 		perror("fork");
// 	return (pid);
// }

// void	setup_child_process(t_cmd *cmd, int input_fd, int output_fd,
// 		int pipe_fds[2])
// {
// 	setup_redirections(input_fd, output_fd, pipe_fds[1]);
// 	close(pipe_fds[0]);
// 	close(pipe_fds[1]);
// 	execvp(cmd->name, build_cmd_args(cmd));
// 	perror("execvp");
// 	exit(EXIT_FAILURE);
// }

// void	handle_parent_process(pid_t pid, int pipe_fds[2], int *status)
// {
// 	close(pipe_fds[1]);
// 	waitpid(pid, status, 0);
// 	print_fd_contents(pipe_fds[0]);
// 	close(pipe_fds[0]);
// }

// void	setup_redirections(int input_fd, int output_fd, int pipe_write_fd)
// {
// 	if (input_fd != -1 && input_fd != STDIN_FILENO)
// 	{
// 		dup2(input_fd, STDIN_FILENO);
// 		close(input_fd);
// 	}
// 	if (output_fd != -1 && output_fd != STDOUT_FILENO)
// 	{
// 		dup2(output_fd, STDOUT_FILENO);
// 		close(output_fd);
// 	}
// 	else
// 		dup2(pipe_write_fd, STDOUT_FILENO);
// }
