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
			ft_putstr_fd("cd: HOME not set\n", 2);
			mini->exit_code = 1;
			return;
		}
	}
	else if(args[1][0] == '-' && args[1][1] == '\0')
	{
		oldpwd = getenv("OLDPWD");
		if(!oldpwd)
		{
			ft_putstr_fd("cd: OLDPWD not set\n", STDERR_FILENO);
			mini->exit_code = 1;
			return;
		}
		path = oldpwd;
		printf("%s\n", path);
	}
	else if (args[0] && args[1] && args[2])
	{
		ft_putstr_fd("bash: cd: too mant arguments\n", STDERR_FILENO);
		mini->exit_code = 1;
		return ;
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
		ft_putstr_fd("cd", STDERR_FILENO);
		mini->exit_code = 1;
		return;
	}
	if(oldpwd)
		setenv("OLDPWD", oldpwd, 1);
	setenv("PWD", new, 1);
	mini->exit_code = 0;
}