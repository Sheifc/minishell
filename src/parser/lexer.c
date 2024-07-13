#include "minishell.h"

void	lexer(char *prompt, t_token **tok)
{
	int	i;

	i = 0;
	while (prompt[i])
	{
		if (prompt[i] == '|')
			set_token(PIPE, prompt, tok, &i);
		else if (prompt[i] == '<')
			set_token(IN, prompt, tok, &i);
		else if (prompt[i] == '>')
			set_token(OUT, prompt, tok, &i);
		else if (prompt[i] == '\'')
			set_token(QUOTE, prompt, tok, &i);
		else if (prompt[i] == '"')
			set_token(DQUOTE, prompt, tok, &i);
		else if (prompt[i] != '|' && prompt[i] != '<' && prompt[i] != '>'
			&& prompt[i] != '\'' && prompt[i] != '"' && prompt[i] != ' ')
			set_token(WORD, prompt, tok, &i);
		else
			i++;
	}
}
