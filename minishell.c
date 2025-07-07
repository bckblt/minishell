#include "minishell.h"

int exit_code = 0;

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_list *mini;
	t_token *tokens = NULL;
	t_cmd *cmd;
	mini = malloc(sizeof(t_list));
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
			exit(0);
			//free lazım
		}
		if(mini->input[0] == '\0')
			continue;
		ft_exit_chk(mini, mini->input);
		add_history(mini->input);
		ft_token(mini->input, &tokens);
		if(!syntax_chk(tokens, mini->input))
		{
			exit_code = 258;
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