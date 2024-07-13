#include "minishell.h"

void	set_token(int type, char *prompt, t_token **tok, int *i)
{
	setter(type, prompt, tok, i);
}
