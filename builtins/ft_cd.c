#include "minishell.h"

void	ft_cd(char **args, t_list *mini)
{
	char *oldpwd;
	char *path;
	char *new;

	if(!args[1])
	{
		path = getenv("HOME");
		if(!path)
		{
			printf("cd: HOME not set\n");
			mini->exit_code = 1;
			return;
		}
	}
	else if(args[1][0] == '-' && args[1][1] == '\0')
	{
		oldpwd = getenv("OLDPWD");
		if(!oldpwd)
		{
			printf("cd: OLDPWD not set\n");
			mini->exit_code = 1;
			return;
		}
		path = oldpwd;
		printf("%s\n", path);
	}
	else
		path = args[1];
	
	oldpwd = getenv("PWD");
	if (chdir(path) != 0)
    {
        perror("cd");
        mini->exit_code = 1;
        return;
    }
	new = getcwd(NULL , 0);
	if(!new)
	{
		perror("cd");
		mini->exit_code = 1;
		return;
	}
	if(oldpwd)
		setenv("OLDPWD", oldpwd, 1);
	setenv("PWD", new, 1);
	mini->exit_code = 0;
}