/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 13:30:37 by sheferna          #+#    #+#             */
/*   Updated: 2024/08/23 19:11:41 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*new_str;
	size_t	i;

	if (s == NULL)
		return (NULL);
	new_str = (char *)malloc(sizeof(char) * (n + 1));
	if (new_str == NULL)
		return (NULL);
	i = -1;
	while (++i < n && s[i] != '\0')
		new_str[i] = s[i];
	new_str[i] = '\0';
	return (new_str);
}
