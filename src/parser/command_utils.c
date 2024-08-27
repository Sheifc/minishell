/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:46:23 by sheferna          #+#    #+#             */
/*   Updated: 2024/08/27 18:51:58 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
void	add_argument(t_cmd *cmd, const char *arg, t_shell *data)
{
	int		i;
	char	**new_args;

	new_args = (char **)malloc((cmd->n_args + 2) * sizeof(char *));
	if (!new_args)
	{
		ft_error(E_MEMORY, NULL, NULL);
		return ;
	}
	i = -1;
	while (++i < cmd->n_args)
		new_args[i] = cmd->arg[i];
	new_args[cmd->n_args] = parse_string(arg, data);
	free(cmd->arg);
	cmd->arg = new_args;
	new_args[cmd->n_args + 1] = NULL;
	cmd->n_args++;
}

// Función crear comando para execvp
char	**build_cmd_args(t_cmd *cmd)
{
	int		i;
	char	**args;

	args = (char **)malloc((cmd->n_args + 2) * sizeof(char *));
	if (!args)
	{
		ft_error(E_MEMORY, NULL, NULL);
		return (NULL);
	}
	args[0] = cmd->name;
	i = -1;
	while (++i < cmd->n_args)
		args[i + 1] = cmd->arg[i];
	args[cmd->n_args + 1] = NULL;
	return (args);
}

// Función para liberar un comando
void	free_commands(t_cmd **head)
{
	int		i;
	t_cmd	*next_node;

	if (*head == NULL)
		return ;
	next_node = (*head)->next;
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
	*head = NULL;
	free_commands(&next_node);
}

// Función para imprimir un nodo de comando (para debug)
void	print_command(t_cmd *cmd)
{
	int			i;
	const char	*symbol_redirect[] = {"None", "Infile", "Outfile"};
	const char	*symbol_parenthesis[] = {"None", "Open", "Close"};

	if (cmd)
	{
		printf(" Command: \e[33m%s\e[0m\n", cmd->name);
		i = -1;
		while (++i < cmd->n_args)
			printf("    Arg[%d]: %s (%lu)\n", i, cmd->arg[i],
				ft_strlen(cmd->arg[i]));
		printf("  \e[34mfd_in: %d\e[0m, \e[35mfd_out: %d\e[0m\n", cmd->fdin,
			cmd->fdout);
		printf("  next_operator: %s [%d]\n", node_type_to_symbol(cmd->operator),
			cmd->operator);
		printf("  \e[36mredirect: %s [%d]\e[0m\n",
			symbol_redirect[cmd->redirect], cmd->redirect);
		printf("  \e[32mparenthesis: %d, parenthesis_status: %s [%d], \e[0m\n",
			cmd->parenthesis, symbol_parenthesis[cmd->parenthesis_status],
			cmd->parenthesis_status);
	}
	else
		printf(" Command: \e[33m(null)\e[0m\n");
}
