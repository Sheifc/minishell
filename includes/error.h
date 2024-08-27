/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:50:06 by sheferna          #+#    #+#             */
/*   Updated: 2024/08/27 18:50:07 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "libft.h"
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef enum e_error_type
{
	E_AUTO = 0,
	E_FILE,
	E_SYNTAX = 2,
	E_FDS = 9,
	E_REDIRECT = 11,
	E_MEMORY = 12,
	E_COMMAND = 127,
	E_UNKNOWN
}		t_error_type;

// Error
void	*ft_error(const int error_code, const char *message, int *status);
void	*ft_error_ope(const int error_code, char *ope, const char *message,
			int *status);
void	*ft_error_syntax(const int error_code, char *ope, const char *message,
			int *status);

#endif
