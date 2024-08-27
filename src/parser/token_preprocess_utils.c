/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_preprocess_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:47:57 by sheferna          #+#    #+#             */
/*   Updated: 2024/08/27 18:47:58 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

char	*remove_quotes(const char *input)
{
	int		len;
	char	*output;
	int		i;
	int		j;

	len = ft_strlen(input);
	output = (char *)malloc((len + 1) * sizeof(char));
	if (!output)
	{
		ft_error(E_MEMORY, NULL, NULL);
		return (NULL);
	}
	j = 0;
	i = -1;
	while (++i < len)
	{
		if (input[i] == '"' || input[i] == '\'')
			continue ;
		if (input[i] == '\\' && i + 1 < len)
			++i;
		output[j++] = input[i];
	}
	output[j] = '\0';
	return (output);
}

// Función para crear una palabra modificada con comillas si es necesario
char	*add_quotes(const char *converted_word, char *quote)
{
	int		new_length;
	char	*modified_word;

	new_length = strlen(converted_word) + 3;
	modified_word = (char *)malloc(new_length * sizeof(char));
	if (!modified_word)
	{
		ft_error(E_MEMORY, NULL, NULL);
		return (NULL);
	}
	ft_strlcpy(modified_word, quote, 2);
	ft_strcat(modified_word, converted_word);
	ft_strcat(modified_word, quote);
	return (modified_word);
}

// Función para obtener la palabra convertida con comillas si es necesario
char	*get_converted_word(const char *palabra, int longitud)
{
	char	*original_word;
	char	*word_without_quotes;
	char	*word_between_quotes;

	original_word = ft_strndup(palabra, longitud);
	word_without_quotes = remove_quotes(original_word);
	word_between_quotes = NULL;
	if (ft_strchr(original_word, '\"'))
		word_between_quotes = add_quotes(word_without_quotes, "\"");
	else if (ft_strchr(original_word, '\''))
		word_between_quotes = add_quotes(word_without_quotes, "\'");
	else
		word_between_quotes = ft_strdup(word_without_quotes);
	free(original_word);
	free(word_without_quotes);
	return (word_between_quotes);
}

void	toggle_between_quotes(t_word_features *ft)
{
	ft->btw_quotes = !(ft->btw_quotes);
	if (ft->new_word)
	{
		ft->start = ft->pos;
		ft->new_word = false;
	}
}

void	handle_spaces_and_operators(const char *in, char **output,
		t_word_features *ft)
{
	if (!ft->new_word)
	{
		process_word(in, ft->start, ft->pos - ft->start, *output);
		ft->new_word = true;
		if (get_operation_size(&in[ft->pos]))
			ft->pos--;
	}
}
