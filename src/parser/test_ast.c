# include "ast.h"

int main() {
	const char *inputs[] = {
        "ls -la | grep 'txt' && cat file.txt > output.txt || echo 'Failed'",
        "(ls -l -a -r | grep 'txt') && (cat file.txt > output.txt || (echo 'Failed' && mkdir new_dir))",
        "mkdir test && cd test || echo 'Could not create directory'",
        "echo 'Starting process'; (cd /tmp && touch temp_file) || echo 'Error in processing'"
    };

    for (int i = 0; i < 4; i++) {
        const char *input = inputs[i];
        int num_tokens;
        Token **tokens = tokenize(input, &num_tokens);

        printf("input:\n%s\n\n", input);
        // print_tokens(tokens, num_tokens);
        // printf("\n");

        ASTNode *ast = build_ast(tokens, num_tokens, 0);
        printf("AST:\n");
        print_ast(ast);

        for (int i = 0; i < num_tokens; i++)
            if (tokens[i])
                free_token2(tokens[i]);
        free(tokens);
        free_ast(ast);
        printf("\n");
    }

    return 0;
    return 0;
}
