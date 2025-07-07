#include "minishell.h"

int char_is_esc(char c) 
{
    return (c == ' ' || c == '|' || c == '>' || c == '<' || c == '&' ||
            c == ';' || c == '(' || c == ')' || c == '$' || c == '"' ||
            c == '\'' || c == '\\' || c == '*' || c == '?' || c == '!' ||
            c == '#' || c == '~' || c == '[' || c == ']' || c == '{' || c == '}');
}

char	*esc_seq(char *inp)
{
	char *new;
	int i = ft_strlen(inp);
	new = malloc(sizeof(char) * i + 1);
	i = 0;
	int j = 0;
	if(!ft_quote_chk(inp))
		return(NULL);
	while(inp[i])
	{
		if(inp[i] == '\\' && char_is_esc(inp[i + 1]))
		{
			new[j] = inp[i + 1];
			i += 2;
			j++;
		}
		else
		{
			new[j] = inp[i];
			i++;
			j++;
		}
	}
	return(new);
}

