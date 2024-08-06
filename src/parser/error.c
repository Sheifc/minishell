#include "error.h"

char	*str_error(int ecode)
{
	if (ecode == E_FILE)
		return ("Input/Output");
    else if (ecode == E_SYNTAX)
		return ("Syntax");
    else if (ecode == E_MEMORY)
		return ("Memory");
    else if (ecode == E_REDIRECT)
		return ("Redirect");
	return ("Unknown");
}

void	ft_error(const int error_code, const char *message, int *status)
{
	if ((message == NULL || ft_strlen(message) == 0) && error_code <= 0)
		fprintf(stderr, "\e[31m Minishell error(%d): %s\e[0m\n",
			errno, strerror(errno));
	else if (error_code <= 0)
		fprintf(stderr, "\e[31m Minishell error(%d): %s\e[0m\n",
			errno, message);
	else if (message == NULL || ft_strlen(message) == 0)
		fprintf(stderr, "\e[31m %s error(%d): %s\e[0m\n",
			str_error(error_code), error_code, strerror(errno));
	else
		fprintf(stderr, "\e[31m %s error(%d): %s\e[0m\n",
			str_error(error_code), error_code, message);
    if (status != NULL && error_code <= 0)
        *status = errno;
    else if (status != NULL)
        *status = error_code;
}

void	ft_error_ope(const int error_code, char *ope, const char *message, int *status)
{
	if ((message == NULL || ft_strlen(message) == 0) && error_code <= 0)
		fprintf(stderr, "\e[31m Minishell error(%d): %s\e[0m\n",
			errno, strerror(errno));
	else if (error_code <= 0)
		fprintf(stderr, "\e[31m Minishell error(%d): %s\e[0m\n",
			errno, message);
	else if (message == NULL || ft_strlen(message) == 0)
		fprintf(stderr, "\e[31m %s error(%d): %s\e[0m\n",
			str_error(error_code), error_code, strerror(errno));
	else
		fprintf(stderr, "\e[31m %s error(%d): \'%s\' %s\e[0m\n",
			str_error(error_code), error_code, ope, message);
    if (status != NULL && error_code <= 0)
        *status = errno;
    else if (status != NULL)
        *status = error_code;
}