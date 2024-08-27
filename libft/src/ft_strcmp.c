/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:43:23 by sheferna          #+#    #+#             */
/*   Updated: 2024/08/23 19:14:00 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = ft_strlen(s2);
	if (n < 1)
		return (0);
	while (n--)
	{
		if (s1[i] != s2[i] || s1[i] == 0 || s2[i] == 0)
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}
