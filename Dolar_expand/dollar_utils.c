#include "minishell.h"

int		if_has_dollar(char *str)
{
	int i = 0;
	while(str[i])
	{
		if(str[i] == '$')
			return(1);
		i++;
	}
	return(0);
}

int		dollar_num(char *str)
{
	int dlr = 0;
	int i = 0;
	while(str[i])
	{
		if(str[i] == '$')
			dlr++;
		i++;
	}
	return(dlr);
}

int get_env_len(char *str, int i)
{
    int start = i + 1;
    char env_name[256];
    int j = 0;
	char *value;

    while (str[start] && (ft_isalnum(str[start]) || str[start] == '_'))
        env_name[j++] = str[start++];
    env_name[j] = '\0';
    value = getenv(env_name);
    if (!value)
        return 0;
    return (ft_strlen(value));
}

int     total_len(char *str)
{
	int i = 0;
	int len = 0;

	while(str[i])
	{
		if(str[i] == '$')
		{
			len += get_env_len(str, i);
			i++;
			while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
				i++;
		}
		else
		{
			len++;
			i++;
		}
	}
	return(len + 1);
}