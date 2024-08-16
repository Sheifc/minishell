#include "minishell.h"

char	*get_current_directory(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		ft_putendl_fd("minishell: getcwd failed: "
		"No such file or directory", 2);
	return (path);
}

void	ft_pwd(t_shell *data)
{
	char	*path;

	path = get_current_directory();
	if (!path)
	{
		data->status = 1;
		return ;
	}
	printf("%s\n", path);
	free(path);
	data->status = 0;
}
