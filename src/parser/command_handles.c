#include "command.h"

// int	handle_pipe(ASTNode *node, int input_fd, int output_fd)
// {
// 	int	pipe_fds[2];
// 	int	left_result;
// 	int	right_result;

// 	if (pipe(pipe_fds) == -1)
// 	{
// 		perror("pipe");
// 		exit(EXIT_FAILURE);
// 	}
// 	left_result = traverse_ast(node->left, input_fd, pipe_fds[1]);
// 	printf(" * (|) result left: %d\n", left_result);
// 	close(pipe_fds[1]);
// 	right_result = traverse_ast(node->right, pipe_fds[0], output_fd);
// 	close(pipe_fds[0]);
// 	return (right_result);
// }

// int	handle_and(ASTNode *node, int input_fd, int output_fd, int left_result)
// {
// 	int	right_result;

// 	printf(" * (AND) result left: %d\n", left_result);
// 	if (left_result == 0)
// 	{
// 		right_result = traverse_ast(node->right, input_fd, output_fd);
// 		return (right_result);
// 	}
// 	return (left_result);
// }

// int	handle_or(ASTNode *node, int input_fd, int output_fd, int left_result)
// {
// 	int	right_result;

// 	printf(" * (OR) result left: %d\n", left_result);
// 	if (left_result != 0)
// 	{
// 		right_result = traverse_ast(node->right, input_fd, output_fd);
// 		return (right_result);
// 	}
// 	return (left_result);
// }

// int	handle_parenthesis(ASTNode *node, int left_result)
// {
// 	printf(" * () result left: %d\n", left_result);
// 	if (node->left)
// 	{
// 		return (left_result);
// 	}
// 	return (-1);
// }

// int	handle_redirections(ASTNode *node, int *input_fd, int *output_fd)
// {
// 	int	fd;
// 	int	pipe_fds[2];
// 	int	left_result;

// 	if (pipe(pipe_fds) == -1)
// 	{
// 		perror("pipe");
// 		exit(EXIT_FAILURE);
// 	}
// 	if (node->right->type == NODE_INPUT)
// 	{
// 		fd = open(node->right->value, O_RDONLY);
// 		if (fd == -1)
// 		{
// 			perror("open input");
// 			exit(EXIT_FAILURE);
// 		}
// 		*input_fd = fd;
// 	}
// 	else if (node->right->type == NODE_OUTPUT)
// 	{
// 		fd = open(node->right->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 		if (fd == -1)
// 		{
// 			perror("open output");
// 			exit(EXIT_FAILURE);
// 		}
// 		*output_fd = fd;
// 	}
// 	else if (node->right->type == NODE_HEREDOC)
// 	{
// 	}
// 	else if (node->right->type == NODE_OUTPUT_APPEND)
// 	{
// 		fd = open(node->right->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
// 		if (fd == -1)
// 		{
// 			perror("open output append");
// 			exit(EXIT_FAILURE);
// 		}
// 		*output_fd = fd;
// 	}
// 	left_result = traverse_ast(node->left, *input_fd, *output_fd);
// 	printf(" * (>) result left: %d\n", left_result);
// 	close(pipe_fds[1]);
// 	return (0);
// }
