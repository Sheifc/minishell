#ifndef ERROR_H
# define ERROR_H

# include "libft.h"
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

// Errors:
//	E_AUTO		-
//	E_FILE		No such file or directory
//	E_FDS		Bad file descriptor
//	E_SYNTAX	Syntax error
//	E_MEMORY	Cannot allocate memory
//	E_UNKNOWN

typedef enum e_error_type
{
	E_AUTO = 0,
	E_FILE,
	E_FDS = 9,
	E_SYNTAX = 10,
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
