#include "minishell.h"

void    ft_pwd(t_list *mini)
{
	char *pwd;

	pwd = getcwd(NULL, 0);
	if(!pwd)
	{
		perror("pwd");
		mini->exit_code = 1;
		return;
	}
	printf("%s\n", pwd);
	free(pwd);
	mini->exit_code = 0;
}