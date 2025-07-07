#ifndef MINISHELL_H
#define MINISHELL_H
 
extern int exit_code;

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "./libft/libft.h"
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>

typedef struct s_list
{
	char **paths;
	char *input;
	char *path;
	char *home;
	char **exp_cpy;
}   t_list;

typedef struct s_token
{
	char *value;
	char *type;
	int quote_num;
	int spc;
	struct s_token *next;
} t_token;

typedef struct s_cmd 
{
	char **command;
	char **redirections;
	int quote_num;
	int pipe_fd[2];
	struct s_cmd *next;
} t_cmd;

void    apply_redirections(char **redirections);
int     node_c(t_cmd *node);
void    ft_cd(char **args);
int     ft_exp(char **env, t_cmd *input);
int     ft_unset(char **env, char *name);
void    paths(char **env, t_list *mini);
void    handle_sig(int signum);
void    ft_exit_chk(t_list *mini, char *input);
void    ft_token(char *input, t_token **tokens);
void    write_list(t_token *tokens);
void    reset_tokens(t_token *tokens);
t_cmd	*ft_parsing(t_token *tokens , t_list *mini);
void	ft_builtins(t_list *mini, t_cmd *cmds, char **env);
void    ft_cmds(t_list *mini, t_cmd *cmd, char **env);
int		syntax_chk(t_token *tokens, char *input);
int		ft_quote_chk(char *inp);
char	*esc_seq(char *inp);
int		char_is_esc(char c) ;
void	ft_echo(t_cmd *cmds, int quote, char *input);
char	*exp_dollar(char *str, int quote);
int		if_has_dollar(char *str);
int		dollar_num(char *str);
int     total_len(char *str);
void	get_exit_code();
int		spc_chk(char *str);
void    ft_pwd();
void	exec_command(char **args, char **paths, char **env);
char	*get_full_path(char *cmd, char **paths);
void    get_pid_echo();
void    ft_env(char **env, char **cmds);
int is_builtin_command(char *cmd);

#endif