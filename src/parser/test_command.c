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
