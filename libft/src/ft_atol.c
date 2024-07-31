/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:48:01 by sheferna          #+#    #+#             */
/*   Updated: 2024/08/01 00:21:59 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_strtol(const char *str, int sign)
{
	long	num;
	int		digit;

	num = 0;
	while (*str >= '0' && *str <= '9')
	{
		digit = *str - '0';
		if (num > (LONG_MAX - digit) / 10)
		{
			errno = ERANGE;
			if (sign == 1)
				return (LONG_MAX);
			else
				return (LONG_MIN);
		}
		num = num * 10 + digit;
		str++;
	}
	return (num);
}

long	ft_atol(const char *str)
{
	long	num;
	int		sign;

	num = 0;
	sign = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	num = ft_strtol(str, sign);
	return (num * sign);
}
