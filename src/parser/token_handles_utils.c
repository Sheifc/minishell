#include "token.h"

bool	is_operator(const char *str)
{
	return (strcmp(str, "&&") == 0 || strcmp(str, "||") == 0 || strcmp(str,
			"|") == 0 || strcmp(str, ";") == 0);
}

int	handle_heredoc_token(char **start, t_shell *data)
{
	if (add_token(start, data, (t_token){T_HEREDOC, "<<", true}) != 0)
		return (1);
	return (handle_redirect_arg(start, data));
}

int	handle_output_append_token(char **start, t_shell *data)
{
	if (add_token(start, data, (t_token){T_OUTPUT_APPEND, ">>", true}) != 0)
		return (1);
	return (handle_redirect_arg(start, data));
}

int	handle_input_token(char **start, t_shell *data)
{
	if (add_token(start, data, (t_token){T_INPUT, "<", true}) != 0)
		return (1);
	return (handle_redirect_arg(start, data));
}

int	handle_output_token(char **start, t_shell *data)
{
	if (add_token(start, data, (t_token){T_OUTPUT, ">", true}) != 0)
		return (1);
	return (handle_redirect_arg(start, data));
}
