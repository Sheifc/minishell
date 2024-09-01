/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 10:31:40 by svilla-d          #+#    #+#             */
/*   Updated: 2024/09/01 10:31:41 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

int	main(void)
{
	t_shell		data;
	bool		is_valid;
	const char	*input = "echo hi > out1 | pwd > out2 | cat < infile";

	printf("\e[35m\n------------------- * -------------------\n\e[0m");
	printf("input:\n%s\n", input);
	data.prompt = (char *)input;
	data.num_tokens = 0;
	data.tokens = tokenize_input(&data);
	data.ast = create_ast(&data);
	is_valid = validate_and_free_tokens(&data);
	data.cmd = generate_commands(&data, is_valid, (t_fds){-1, -1});
	print_commands(data.cmd);
	free_commands(&data.cmd);
	return (0);
}
