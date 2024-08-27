/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_preprocess_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:48:25 by sheferna          #+#    #+#             */
/*   Updated: 2024/08/27 18:48:26 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

char	*remove_repeated_chars(const char *str, char ch)
{
	char	*result;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	result = (char *)malloc(strlen(str) + 1);
	if (!result)
		return (NULL);
	result[0] = str[0];
	i = 1;
	j = 1;
	while (str[i] != '\0')
	{
		if (str[i] != ch || str[i] != str[i - 1])
		{
			result[j] = str[i];
			j++;
		}
		i++;
	}
	result[j] = '\0';
	return (result);
}
