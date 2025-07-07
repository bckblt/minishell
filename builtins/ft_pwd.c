#include "minishell.h"

void    ft_pwd()
{
	char *pwd;

	pwd = getcwd(NULL, 0);
	if(!pwd)
	{
		perror("pwd");
		exit_code = 1;
		return;
	}
	printf("%s\n", pwd);
	free(pwd);
	exit_code = 0;
}