#include "minishell.h"

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_list *mini;
	t_token *tokens = NULL;
	t_cmd *cmd;
	mini = malloc(sizeof(t_list));
	cmd = malloc(sizeof(t_cmd));
	if (!mini)
		return (0);
	ft_memset(mini, 0, sizeof(t_list));
	paths(env, mini);
	signal(SIGINT, handle_sig);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		mini->input = readline("minishell$ ");
		if(!mini->input)
		{
			printf("exit\n");
			exit(mini->exit_code);
		}
		if(mini->input[0] == '\0')
			continue;
		if(!ft_exit_chk(mini, mini->input))
			continue;
		add_history(mini->input);
		ft_token(mini->input, &tokens);
		if(!syntax_chk(tokens, mini->input))
		{
			mini->exit_code = 258;
			printf("Syntax Error\n");
			reset_tokens(tokens);
			tokens = NULL;
			continue; 
		}
		cmd = ft_parsing(tokens, mini);
		reset_tokens(tokens);
		tokens = NULL;
		if(cmd == NULL)
			continue;
		ft_builtins(mini, cmd, env);
	}
	return (0);
}