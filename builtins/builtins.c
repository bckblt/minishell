#include "minishell.h"

int ft_envlen(char **env)
{
	int i = 0;
	while (env[i])
		i++;
	return i;
}

int ft_short(char **env)
{
	int i = 0;
	int j;
	char *temp;
	
	if (!env)
		return (1);
		
	while (env[i] && env[i + 1])
	{
		j = i + 1;
		while (env[j])
		{
			if (strcmp(env[i], env[j]) > 0)
			{
				temp = env[i];
				env[i] = env[j];
				env[j] = temp;
			}
			j++;
		}
		i++;
	}
	return (0);
}

int ft_exp(char **env, t_cmd *input)
{
	char **inp = input->command;

	if (!inp[1])
	{
		int env_len = ft_envlen(env);
		char **env_copy = malloc(sizeof(char *) * (env_len + 1));
		if (!env_copy)
			return 1;
		for (int i = 0; i < env_len; i++)
			env_copy[i] = ft_strdup(env[i]);
		env_copy[env_len] = NULL;

		ft_short(env_copy);
		for (int i = 0; env_copy[i]; i++)
		{
			printf("declare -x %s\n", env_copy[i]);
			free(env_copy[i]);
		}
		free(env_copy);
		return 0;
	}
	char *eq = strchr(inp[1], '=');
	char *to_add;
	if (eq)
	{
		to_add = strdup(inp[1]);
	}
	else
	{
		to_add = malloc(strlen(inp[1]) + 2);
		sprintf(to_add, "%s=", inp[1]);
	}
	int i = 0;
	int updated = 0;

	while (env[i])
	{
		if (strncmp(env[i], inp[1], eq - inp[1]) == 0 && env[i][eq - inp[1]] == '=')
		{
			free(env[i]);
			env[i] = strdup(inp[1]);
			updated = 1;
			break;
		}
		i++;
	}
	if (!updated)
	{
		int len = ft_envlen(env);
		env[len] = strdup(inp[1]);
		env[len + 1] = NULL;
	}
	return 0;
}

int ft_unset(char **env, char *var_name)
{
	int i = 0;
	int var_len;
	int removed = 0;

	if (!var_name)
	{
		printf("unset: not enough arguments\n");
		return (1);
	}
	var_len = ft_strlen(var_name);
	while (env[i])
	{
		if (ft_strncmp(env[i], var_name, var_len) == 0 && env[i][var_len] == '=')
		{
			free(env[i]);
			int j = i;
			while (env[j + 1])
			{
				env[j] = env[j + 1];
				j++;
			}
			env[j] = NULL; 
			removed = 1;
			break;
		}
		i++;
	}
	if (!removed)
	{
		fprintf(stderr, "unset: `%s`: not found\n", var_name);
		return (1);
	}
	return (0);
}

void ft_builtins(t_list *mini, t_cmd *cmds, char **env)
{
    int is_builtin = is_builtin_command(cmds->command[0]);
    
    if (is_builtin && !cmds->next)
    {
        if (cmds->redirections)
            if(apply_redirections(cmds->redirections, cmds->fd) == -1)
                return;

        if(ft_strncmp(cmds->command[0], "exit", 4) == 0)
            return;
        if (ft_strncmp(cmds->command[0], "echo", 4) == 0)
            ft_echo(cmds, cmds->quote_num, mini->input);
        if (ft_strncmp(cmds->command[0], "pwd", 3) == 0)
            ft_pwd();
        if (ft_strncmp(cmds->command[0], "cd", 2) == 0)
            ft_cd(cmds->command);
        if (ft_strncmp(cmds->command[0], "export", 6) == 0)
            ft_exp(env, cmds);
        if (ft_strncmp(cmds->command[0], "unset", 5) == 0)
            ft_unset(env, cmds->command[1]);
        if (ft_strncmp(cmds->command[0], "env", 3) == 0)
            ft_env(env, cmds->command);
        
        if (cmds->redirections)
            retfd(cmds);
        
        return;
    }
    
    ft_cmds(mini, cmds, env);
}