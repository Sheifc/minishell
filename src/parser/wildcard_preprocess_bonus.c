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
