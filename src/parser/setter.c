#include "minishell.h"

void	append_hdoc_tok(char *prompt, t_token **tok, int *i)
{
	if (prompt[*i] == '<')
		heredoc_in(prompt, tok, i);
	else if (prompt[*i] == '>')
		append_out(prompt, tok, i);
}

void	word_tok(char *prompt, t_token **tok, int *i)
{
	int	start;

	start = *i;
	while (prompt[*i] && prompt[*i] != '|' && prompt[*i] != '<'
		&& prompt[*i] != '>' && prompt[*i] != ' ' && prompt[*i] != '\''
		&& prompt[*i] != '"')
		*i += 1;
	create_list(WORD, tok, ft_substr(prompt, start, *i - start));
}

void	quote_tok(char *prompt, t_token **tok, int *i)
{
	int	start;
	int	qflag;

	start = *i;
	qflag = quote_stuff(i, prompt);
	if (qflag > 0)
		create_list(QUOTE, tok, ft_substr(prompt, start + 1, qflag));
	else if (qflag < 0)
		(*tok) = NULL;
	*i += 1;
}

void	dquote_tok(char *prompt, t_token **tok, int *i)
{
	int	start;
	int	qflag;

	start = *i;
	qflag = dquote_stuff(i, prompt);
	if (qflag > 0)
		create_list(DQUOTE, tok, ft_substr(prompt, start + 1, qflag));
	else if (qflag < 0)
		(*tok) = NULL;
	*i += 1;
}

void	setter(int type, char *prompt, t_token **tok, int *i)
{
	if (prompt[*i] && type == PIPE)
	{
		create_list(type, tok, ft_strdup("|"));
		*i += 1;
	}
	else if (prompt[*i] && type == IN)
		append_hdoc_tok(prompt, tok, i);
	else if (prompt[*i] && type == OUT)
		append_hdoc_tok(prompt, tok, i);
	else if (prompt[*i] && type == WORD)
		word_tok(prompt, tok, i);
	else if (prompt[*i] && type == QUOTE)
		quote_tok(prompt, tok, i);
	else if (prompt[*i] && type == DQUOTE)
		dquote_tok(prompt, tok, i);
}
