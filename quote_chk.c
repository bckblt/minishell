#include "minishell.h"

int		single_quote_chk(char *inp, int i)
{
	int tmp = i;
	while(inp[i])
	{
		if(inp[i] == '\'')
			return(0);
		i++;
	}
	i = tmp;
	while(inp[i])
	{
		if(inp[i] == '\'')
			return(0);
		i--;
	}
	return(1);
}

int		double_quote_chk(char *inp, int i)
{
	int tmp = i;
	while(inp[i])
	{
		if(inp[i] == '\"')
			return(0);
		i++;
	}
	i = tmp;
	while(inp[i])
	{
		if(inp[i] == '\"')
			return(0);
		i--;
	}
	return(1);
}

int		ft_quote_chk(char *inp)
{
	int i = 0;
	int single_num = 0;
	int double_num = 0;
	
	while(inp[i])
	{
		if(inp[i] == '\'' && double_quote_chk(inp, i))
			single_num++;
		if(inp[i] == '"' && inp[i - 1] != '\\' && single_quote_chk(inp, i))
			double_num++;
		i++;
	}
	if(single_num % 2 != 0 || double_num % 2 != 0)
		return(0);
	if(inp[i - 1] == '\\')
		return(0);
	return(1);
}

