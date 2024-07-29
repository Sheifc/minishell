#include "token.h"

char	*process_word(const char *input, int start, int length, char *output)
{
	char	*word;

	word = get_converted_word(input + start, length);
	output = ft_strcat(output, word);
	output = ft_strcat(output, " ");
	free(word);
	return (output);
}

int	get_operation_size(const char *str)
{
	if (ft_strcmp(str, "&&") == 0 || ft_strcmp(str, "||") == 0)
		return (2);
	if (ft_strcmp(str, "|") == 0 || ft_strcmp(str, ";") == 0 || ft_strcmp(str,
			"(") == 0 || ft_strcmp(str, ")") == 0)
		return (1);
	return (0);
}

void	handle_character(const char *in, char **output, t_word_features *ft)
{
	if (in[ft->pos] == '"' || in[ft->pos] == '\'')
		toggle_between_quotes(ft);
	else if (get_operation_size(&in[ft->pos]) && !ft->btw_quotes
		&& ft->new_word)
	{
		process_word(in, ft->pos, get_operation_size(&in[ft->pos]), *output);
		ft->new_word = true;
		ft->pos = ft->pos + get_operation_size(&in[ft->pos]) - 1;
		ft->start = ft->pos;
	}
	else if ((in[ft->pos] == ' ' || get_operation_size(&in[ft->pos]))
		&& !ft->btw_quotes)
		handle_spaces_and_operators(in, output, ft);
	else
	{
		if (ft->new_word)
		{
			ft->start = ft->pos;
			ft->new_word = false;
		}
	}
}

bool	ok_count_quotes(const char *str)
{
	int	count;
	int	i;

	count = 0;
	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '"')
			++count;
	}
	if (count % 2 == 0)
		return (true);
	return (false);
}

char	*preprocess_input(const char *input)
{
	char			*output;
	t_word_features	feat;
	int				len;

	if (ok_count_quotes(input) == false)
		return ((char *)input);
	len = ft_strlen(input);
	feat.btw_quotes = false;
	feat.new_word = true;
	feat.start = 0;
	output = (char *)malloc((len + 1) * sizeof(char));
	output[0] = '\0';
	feat.pos = -1;
	while (++feat.pos <= len)
		handle_character(input, &output, &feat);
	if (!feat.new_word)
		process_word(input, feat.start, len - feat.start, output);
	return (output);
}
