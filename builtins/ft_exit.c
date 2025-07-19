#include "minishell.h"

char *quote_del(char *str)
{
	int i = 0;
	int j = 0;
	char *tmp;
	tmp = malloc(sizeof(char) * ft_strlen(str) + 1);
	while(str[i])
	{
		if(str[i] == '\"')
			i++;
		tmp[j] = str[i];
		j++;
		i++;
	}
	tmp[j] = '\0';
	return(tmp);
}

int    exit_with_arg(char *inp, t_list *mini)
{
	char *err;
	int len = ft_strlen(inp);  
	int i = 5;
	char **chk;
	int num;

	chk = ft_split(inp, ' ');
	inp = quote_del(inp);
	if (ft_strncmp(inp, "exit", 4) == 0 && (inp[4] == '\0'))
	{
		printf("%d\n", mini->exit_code);
		mini->exit_code = 0;
		exit (mini->exit_code);
	}
	if(chk[1] && chk[2])
	{
		print_error(" too many arguments\n");	
		mini->exit_code = 1;
		free(chk);
		return(1);
	}
	while(inp[i])
	{
		if(!ft_isdigit(inp[i]))
		{
			printf("exit\n");
			print_error(" numeric argument required\n");
			mini->exit_code = 255;
			exit(mini->exit_code);
			return(2);
		}
		else
		{
			err = ft_substr(inp, i, len);
			printf("exit\n");
			num = ft_atoi(err);
			if(num < 0)
				mini->exit_code = (unsigned int)num;
			else
				mini->exit_code = num;
			//printf("%d\n", mini->exit_code);
			free(err);
			exit(mini->exit_code);
			return(3);
		}
		i++;
	}
	return(4);
}

int	ft_exit_chk(t_list *mini, char *input)
{
	int exit_res;
	if (!input)
	{
		free(mini->path);
		free(mini);
		exit(mini->exit_code);
	}
	if ((ft_strncmp(input, "exit", 4) == 0) && (input[4] == ' ' || input[4] == '\0'))
	{
		exit_res = exit_with_arg(input, mini);
		if(exit_res == 1)
			return(0);
		else
		{
			free(input);
			free(mini->path);
			free(mini);
			//printf("%d\n", mini->exit_code);
			exit(mini->exit_code);
		}
	}
	return(1);
}