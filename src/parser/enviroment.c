/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:46:40 by sheferna          #+#    #+#             */
/*   Updated: 2024/08/27 18:46:41 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "minishell.h"

char	*create_new_result(const char *result, const char *pos,
		const char *value, const char *name)
{
	char	*new_result;
	size_t	new_length;

	new_length = ft_strlen(result) + ft_strlen(value) - ft_strlen(name) - 1;
	new_result = (char *)malloc((new_length + 1) * sizeof(char));
	if (!new_result)
	{
		ft_error(E_MEMORY, NULL, NULL);
		return (NULL);
	}
	ft_strncpy(new_result, result, pos - result);
	ft_strcpy(new_result + (pos - result), value);
	ft_strcpy(new_result + (pos - result) + ft_strlen(value), pos
		+ ft_strlen(name) + 1);
	return (new_result);
}

char	*replace_variable(const char *pos, char *result, const char *name,
		t_shell *data)
{
	char	*value;
	char	*new_result;

	if (ft_strncmp((pos + 1), "?", 1) != 0)
		value = get_value(data->env, name);
	else
		value = (char *)name;
	if (value)
		new_result = create_new_result(result, pos, value, name);
	else
		new_result = create_new_result(result, pos, "", name);
	if (!new_result)
		return (NULL);
	free(result);
	return (new_result);
}

int	is_preceded_by_double_less(const char *str, const char *pos)
{
	const char	*p;

	p = pos - 1;
	while (p > str && ft_strchr(DELIMITERS, *p))
		p--;
	if (p > str && *p == '<')
	{
		p--;
		if (p > str && *p == '<')
			return (1);
	}
	return (0);
}

char	*replace_env_variables(const char *input, t_shell *data)
{
	char	*result;
	char	*pos;
	char	*var_name;

	result = initialize_result(input);
	pos = ft_strchr(result, '$');
	while (pos)
	{
		if (is_btw_single_quotes(result, pos)
			|| is_preceded_by_double_less(result, pos) || (*(pos + 1) == ' '
				|| *(pos + 1) == '\0'))
		{
			pos = ft_strchr(pos + 1, '$');
			continue ;
		}
		if (ft_strncmp((pos + 1), "?", 1) != 0)
			var_name = extract_variable_name(pos + 1);
		else
			var_name = ft_itoa(data->status);
		result = replace_variable(pos, result, var_name, data);
		free(var_name);
		pos = ft_strchr(result, '$');
	}
	return (result);
}
