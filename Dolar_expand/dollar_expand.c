#include "minishell.h"

int		pass_env(char *str, int i)
{
	if(str[i + 1] == '{')
		i += 2;
	else
		i += 1;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_') && str[i] != '$')
		i++;
	if(str[i] == '}')
		i++;
	return (i);
}

char	*take_env(char *str, int i)
{
	char *tmp;
	int j = 0;
	char *value;
	int len = 0;

	len = pass_env(str, i);
	tmp = malloc(sizeof(char) * len + 1);
	if (!tmp)
		return NULL;
	if(str[i + 1] == '{')
		i += 2;
	else
		i++;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_') && str[i] != '"' && str[i] != '}')
		tmp[j++] = str[i++];
	tmp[j] = '\0';
	value = getenv(tmp);
	free(tmp);
	if (!value)
		return ft_strdup("");
	return ft_strdup(value);
}

char	*esc_chk(char *str)
{
	char *tmp;
	int len;
	len = ft_strlen(str);
	int i = 0;

	tmp = malloc(sizeof(char) * len);
	len = 0;
	while(str[i])
	{	
		if(str[i] == '\\')
			i++;
		tmp[len] = str[i];
		i++;
		len++;
	}
	tmp[len] = '\0';
	return(tmp);
}

int		special_dlr(char *str)
{
	int i = 0;
	while(str[i])
	{
		if(str[i] == '$' && str[i + 1] == '$')
			return(1);
		else if(str[i] == '$' && str[i + 1] == '?')
			return(1);
		i++;
	}
	return(0);
}

char *exp_dollar(char *str, int quote)
{
    int i = 0;
	int j = 0;
	int k = 0;
    char *tmp;
    char *tmp2;

	k = total_len(str);
	tmp = malloc(sizeof(char) * k);
	k = 0;
    if (!tmp)
        return NULL;
    if (if_has_dollar(str) == 0 || quote == 1 || special_dlr(str))
	{
        return (str);
	}
	if (ft_strncmp(str, "$$", 2) == 0 || ft_strncmp(str, "$?", 2) == 0 )
		return(str);
	while(str[i])
	{
		if(str[i] == '$' && str[i - 1] == '\\')
		{
			tmp = esc_chk(str);
			return(tmp);
		}
		i++;
	}
	i = 0;
    while (str[i])
    {
        if (str[i] == '$' && (str[i + 1] != '$' && 	str[i + 1] != '?') && str[i + 1] != '\0')
        {
            tmp2 = take_env(str, i);
            k = 0;
            while (tmp2[k])
                tmp[j++] = tmp2[k++];
            free(tmp2);
            i = pass_env(str, i);
            continue;
        }
        tmp[j++] = str[i++];
    }
    tmp[j] = '\0';
    return tmp;
}
