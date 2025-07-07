#include "minishell.h"

void    ft_env(char **env, char **cmds)
{
    int i = 0;
    char *er;
    if(cmds[1] != NULL)
    {   
        er = cmds[1];
        printf("env: %s: No such file or directory\n", er);
        return;
    }
    while(env[i])
    {
        printf("%s\n", env[i]);
        i++;
    }
}