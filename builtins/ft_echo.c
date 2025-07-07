#include "minishell.h"

void    get_pid_echo()
{
	int pid = getpid();
	ft_putnbr_fd(pid, 0);
}

void	get_exit_code()
{
	ft_putnbr_fd(exit_code, 0);
}

void    ft_echo_n(char **strngs)
{
	int i = 2;
	int j = 0;

	while(strngs[i])
	{
		j = 0;
		if(ft_strncmp("-n", strngs[i], 2) == 0)
		{
			i++;
			continue;
		}
		while(strngs[i][j])
		{
			if(strngs[i][j] == '$' && strngs[i][j + 1] == '$')
			{
				get_pid_echo();
				j += 2;
				continue;
			}
			else if(strngs[i][j] == '$' && strngs[i][j + 1] == '?')
			{
				get_exit_code();
				exit_code = 0;
				j += 2;
				continue;
			}
			write(1, &strngs[i][j], 1);
			j++;
		}
		if (strngs[i + 1] && strngs[i][0] != '\0')
			write(1, " ", 1);
		i++;
	}
}

void    ft_echo(t_cmd *cmds, int quote, char *input)
{
	int i = 1;
	int j = 0;
	int spc = spc_chk(input);
	char **strngs = cmds->command;

	while(strngs[i])
	{
		j = 0;
		if(ft_strncmp("-n", strngs[1], 2) == 0)
		{
			ft_echo_n(strngs);
			return;
		}
		while(strngs[i][j])
		{
			if(strngs[i][j] == '$' && strngs[i][j + 1] == '$' && quote != 1)
			{
				get_pid_echo();
				j += 2;
				continue;
			}
			else if(strngs[i][j] == '$' && strngs[i][j + 1] == '?' && quote != 1)
			{
				get_exit_code();
				exit_code = 0;
				j += 2;
				continue;
			}
			if(cmds->redirections[0] == NULL)
				write(1, &strngs[i][j], 1); 
			j++;
		}
		if (strngs[i + 1] && strngs[i][0] != '\0' && spc != 0) 
			write(1, " ", 1);
		i++;
	}
	if(cmds->redirections[0] == NULL)
		write(1, "\n", 1);
}