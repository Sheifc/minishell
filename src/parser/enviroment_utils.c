/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:46:36 by sheferna          #+#    #+#             */
/*   Updated: 2024/08/27 18:46:37 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

char	*initialize_result(const char *input)
{
	char	*result;

	result = (char *)malloc((ft_strlen(input) + 1) * sizeof(char));
	if (!result)
	{
		ft_error(E_MEMORY, NULL, NULL);
		return (NULL);
	}
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
