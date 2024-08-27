/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:33:53 by sheferna          #+#    #+#             */
/*   Updated: 2024/08/23 19:13:50 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dest, const char *src)
{
	char	*ptr;

	ptr = dest + ft_strlen(dest);
	while (*src != '\0')
		*ptr++ = *src++;
	*ptr = '\0';
	return (dest);
}
