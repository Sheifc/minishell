#include "minishell.h"

void    free_all(t_shell *data)
{
    if (data->prompt)
    {
        free(data->prompt);
        data->prompt = NULL;
    }
    if (data->env)
    {
        free_env_list(data->env);
        data->env = NULL;
    }
    if (data->export)
    {
        free_env_list(data->export);
        data->export = NULL;
    }
    if (data->token)
        free_token_list(&data->token);
    if (data->cmd)
        free_cmd_list(&data->cmd);
}

void clear_structs(t_token **token, t_cmd **cmd)
{
    if (token)
        free_token_list(token);
    if (cmd && *cmd)
        free_cmd_list(cmd);
}
