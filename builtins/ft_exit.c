#include "minishell.h"

int    exit_with_arg(char *inp)
{
	char *err;
	int len = ft_strlen(inp);  
	int i = 5;
	char **chk;
	int num;
	chk = ft_split(inp, ' ');
	if(chk[1] && chk[2])
	{
		printf("minishell: exit: too many arguments\n");	
		exit_code = 1;
		free(chk);
		return(1);
	}
	while(inp[i])
	{
		if(inp[i] == '-')
			i++;
		if(!ft_isdigit(inp[i]))
		{
			err = ft_substr(inp, i, len);
			printf("exit\n");
			printf("minishell: exit: %s: numeric argument required\n", err);
			exit_code = 255;
			free(err);
			return(2);
		}
		else
		{
			err = ft_substr(inp, i, len);
			printf("exit\n");
			num = ft_atoi(err);
			if(num < 0)
				exit_code = (unsigned int)num;
			else
				exit_code = num;
			free(err);
			return(3);
		}
		i++;
	}
	return(4);
}

void    ft_exit_chk(t_list *mini, char *input)
{
	int exit_res;
	if (!input)
	{
		free(mini->path);
		free(mini);
		exit(0);
	}
	if (!ft_strncmp(input, "exit", 4) && (input[4] == ' ' || input[4] == '\0'))
	{
		exit_res = exit_with_arg(input);
		if(exit_res != 1)
		{
			free(input);
			free(mini->path);
			free(mini);
			exit(0);
		}
	}
}