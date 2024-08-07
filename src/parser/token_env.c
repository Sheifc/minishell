#include "token.h"

char	*initialize_result(const char *input)
{
	char	*result;

	result = (char *)malloc((strlen(input) + 1) * sizeof(char));
	ft_strcpy(result, input);
	return (result);
}

char	*extract_variable_name(const char *start)
{
	char	var_name[256];
	int		var_length;
	char	*var_name_dynamic;

	var_length = 0;
	while (*start && (ft_isalnum(*start) || *start == '_'))
	{
		var_name[var_length++] = *start;
		start++;
	}
	var_name[var_length] = '\0';
	var_name_dynamic = (char *)malloc((var_length + 1) * sizeof(char));
	if (!var_name_dynamic)
	{
		ft_error(E_MEMORY, NULL, NULL);
		return (NULL);
	}
	ft_strcpy(var_name_dynamic, var_name);
	return (var_name_dynamic);
}

char	*replace_variable(const char *pos, char *result, const char *name)
{
	char	*value;
	char	*new_result;
	size_t	new_length;

	if (ft_strncmp((pos + 1), "?", 1) !=0)
		value = getenv(name);
	else
		value = (char *)name;
	if (value)
	{
		new_length = ft_strlen(result) + ft_strlen(value) - ft_strlen(name) - 1;
		new_result = (char *)malloc((new_length + 1) * sizeof(char));
		if (!new_result)
		{
			ft_error(E_MEMORY, NULL, NULL);
			return (NULL);
		}
		strncpy(new_result, result, pos - result);
		ft_strcpy(new_result + (pos - result), value);
		ft_strcpy(new_result + (pos - result) + ft_strlen(value), pos
			+ ft_strlen(name) + 1);
		free(result);
		return (new_result);
	}
	else
	{
		new_length = ft_strlen(result) - ft_strlen(name) - 1;
		new_result = (char *)malloc((new_length + 1) * sizeof(char));
		if (!new_result)
		{
			ft_error(E_MEMORY, NULL, NULL);
			return (NULL);
		}
		strncpy(new_result, result, pos - result);
		ft_strcpy(new_result + (pos - result), pos + ft_strlen(name) + 1);
		free(result);
		return (new_result);
	}
}

int	is_btw_single_quotes(const char *str, const char *pos)
{
	int			in_single_quotes;
	const char	*ptr;

	in_single_quotes = 0;
	ptr = str;
	while (ptr < pos)
	{
		if (*ptr == '\'')
			in_single_quotes = !in_single_quotes;
		ptr++;
	}
	return (in_single_quotes);
}

int is_preceded_by_double_less(const char *str, const char *pos) {
    const char *p;

	p = pos - 1;
    while (p > str && ft_strchr(DELIMITERS, *p))
        p--;
    if (p > str && *p == '<')
	{
        p--;
        if (p > str && *p == '<')
            return 1;
    }
    return 0;
}

char	*replace_env_variables(const char *input, int status)
{
	char	*result;
	char	*pos;
	char	*var_name;

	result = initialize_result(input);
	pos = ft_strchr(result, '$');
	while (pos)
	{
		if (is_btw_single_quotes(result, pos) || is_preceded_by_double_less(result, pos))
		{
			pos = ft_strchr(pos + 1, '$');
			continue ;
		}
		if (ft_strncmp((pos + 1), "?", 1) !=0)
			var_name = extract_variable_name(pos + 1);
		else
			var_name = ft_itoa(status);
		result = replace_variable(pos, result, var_name);
		free(var_name);
		pos = ft_strchr(result, '$');
	}
	return (result);
}
