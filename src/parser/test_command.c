#include "command.h"


void execute_commands(Command *commands) {
    Command *current = commands;
    pid_t pid;
    int status;

    while (current) {
		printf("\e[0m - Ejecutando comando: \e[33m%s\e[0m -\e[32m\n", current->name);
		if (current->operator == NODE_END && (ft_strncmp(current->name, "save_outfile", 12) == 0 || ft_strncmp(current->name, "save_append", 12) == 0)){
		} else {
			if (ft_strncmp(current->name, "read_infile", 11) == 0)
			{
				if (current->fdin != STDIN_FILENO) {
					close(current->fdin);
				}
				current = current->next;
				continue ;
			}
			if (ft_strncmp(current->name, "save_outfile", 12) == 0 || ft_strncmp(current->name, "save_append", 12) == 0){
				current->name = ft_strdup("cat");
				current->arg[0] = ft_strdup("cat");
			} 
			pid = fork();

			if (pid == 0) {
				// Child process
				if (current->fdin != STDIN_FILENO) {
					dup2(current->fdin, STDIN_FILENO);
					close(current->fdin);
				}
				if (current->fdout != STDOUT_FILENO) {
					dup2(current->fdout, STDOUT_FILENO);
					close(current->fdout);
				}
				execvp(current->name, current->arg);
				perror("execvp");
				exit(EXIT_FAILURE);
			} else if (pid < 0) {
				perror("fork");
				exit(EXIT_FAILURE);
			}

			// Parent process
			if (current->fdin != STDIN_FILENO) {
				close(current->fdin);
			}
			if (current->fdout != STDOUT_FILENO) {
				if (!current->next || current->next->fdout != current->fdout)
				close(current->fdout);
			}

			// Wait for the child process to finish
			waitpid(pid, &status, 0);
			printf("\e[0m");
			// Check if the command was executed successfully
			if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
				fprintf(stderr, "Command failed with status %d: %s\n", WEXITSTATUS(status), current->name);
			}
		}
        // Move to the next command
        current = current->next;
    }
}

int	main(void)
{
	const char	*input;
	Token		**tokens;
	ASTNode		*ast;
	Command		*cmd = NULL;
	Command		*current = NULL;
	bool		is_valid;
	int			num_tokens;

	input = "echo hola | cat > out1.txt";
	printf("\e[35m\n------------------- * -------------------\n\e[0m");
	tokens = tokenize(input, &num_tokens);
	printf("input:\n%s\n", input);
	printf("\n**** Tokens: ****\n");
	print_tokens(tokens, num_tokens);
	verify_tokens(tokens, &num_tokens);
	ast = build_ast(tokens, num_tokens, 0);
	printf("\n**** AST: ****\n");
	print_ast(ast);
	is_valid = validate_ast(tokens, ast);
	printf("\n**** Generating Commands: ****\n");
	OperatorStack *ope_stack = NULL;
	PipeStack *pipe_stack = NULL;
	Fds fds;
	fds.in = STDIN_FILENO;
	fds.out = STDOUT_FILENO;
	if (is_valid)
		cmd = traverse_ast(ast, fds, &ope_stack, &pipe_stack);
	current = cmd;
	printf("\n**** List ofCommands: ****\n");
	while (current)
	{
		print_command(current);
		current = current->next;

	}
	printf("\n**** Ejecutando: ****\n");
	execute_commands(cmd);
	
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
