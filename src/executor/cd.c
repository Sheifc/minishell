#include "minishell.h"

t_env	*env_lst_search(t_env *env, const char *key)
{
	while (env)
	{
		if (!ft_strncmp(env->key, key, ft_strlen(key) + 1))
			return (env);
		env = env->next;
	}
	return (NULL);
}

static int	update_pwd_oldpwd(t_env *env, const char *key, char *value)
{
	t_env	*temp_env;

	temp_env = env_lst_search(env, key);
	if (temp_env)
	{
		free(temp_env->value);
		temp_env->value = ft_strdup(value);
		if (!temp_env->value)
			return (0);
	}
	return (1);
}

static char	*get_pwd(t_shell *data, t_cmd *cmd, char *path)
{
	if (cmd->n_args == 1 || !ft_strncmp(cmd->arg[1], "~\0", 2))
	{
		path = get_cd_value(data->env, "HOME");
		if (!path)
		{
			ft_putendl_fd("minishell: cd: HOME not set", 2);
			data->status = 1;
		}
	}
	else if (!ft_strncmp(cmd->arg[1], "-", 1))
	{
		path = get_cd_value(data->env, "OLDPWD");
		if (!path)
		{
			ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
			data->status = 1;
		}
	}
	else
		path = cmd->arg[1];
	return (path);
}

static void	update_variables(char *new_pwd, char *old_pwd, t_shell *data)
{
	if (!new_pwd)
	{
		free(old_pwd);
		perror("Error: getting the new directory");
	}
	if (!update_pwd_oldpwd(data->env, "OLDPWD", old_pwd)
		|| !update_pwd_oldpwd(data->export, "OLDPWD", old_pwd))
	{
		free(old_pwd);
		free(new_pwd);
		perror("Error: updating OLDPWD");
	}
	if (!update_pwd_oldpwd(data->env, "PWD", new_pwd)
		|| !update_pwd_oldpwd(data->export, "PWD", new_pwd))
	{
		free(old_pwd);
		free(new_pwd);
		perror("Error: updating PWD");
	}
}

void	check_args(t_shell *data, t_cmd *cmd)
{
	if (cmd->n_args > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		data->status = 1;
	}
}

void	ft_cd(t_shell *data, t_cmd *cmd)
{
	char	*pwd;
	char	*old_pwd;
	char	*new_pwd;

	pwd = NULL;
	check_args(data, cmd);
	old_pwd = get_current_directory();
	if (!old_pwd)
	{
		data->status = 1;
		return ;
	}
	pwd = get_pwd(data, cmd, pwd);
	if (!pwd)
	{
		free(old_pwd);
		data->status = 1;
		return ;
	}
	if (chdir(pwd) < 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(pwd, 2);
		ft_putendl_fd(": No such file or directory", 2);
		data->status = 1;
	}
	new_pwd = get_current_directory();
	update_variables(new_pwd, old_pwd, data);
	if(old_pwd)
		free(old_pwd);
	if(new_pwd)
		free(new_pwd);
	if (data->status == 1)
		data->status = 1;
	else
		data->status = 0;
}
