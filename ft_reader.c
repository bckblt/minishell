#include "minishell.h"

void exec_builtin(t_cmd *cmd, t_list *mini, char **env)
{
    if (ft_strncmp(cmd->command[0], "cd", 2) == 0)
        ft_cd(cmd->command);
    else if (ft_strncmp(cmd->command[0], "echo", 4) == 0)
        ft_echo(cmd, cmd->quote_num, mini->input);
    else if (ft_strncmp(cmd->command[0], "pwd", 3) == 0)
        ft_pwd();
    else if (ft_strncmp(cmd->command[0], "export", 6) == 0)
        ft_exp(env, cmd);
    else if (ft_strncmp(cmd->command[0], "unset", 5) == 0)
        ft_unset(env, cmd->command[1]);
    else if (ft_strncmp(cmd->command[0], "env", 3) == 0)
        ft_env(env, cmd->command);
    exit(0);
}

void    ft_cmds(t_list *mini, t_cmd *cmd, char **env)
{
    int prev_pipe_in = -1;
    int pipe_fd[2];
    int is_builtin;

    while (cmd)
    {
        is_builtin = is_builtin_command(cmd->command[0]);
        
        if (cmd->next)
            pipe(pipe_fd);

        pid_t pid = fork();
        if (pid == 0)
        {
            if (cmd->redirections)
                apply_redirections(cmd->redirections);
            
            if (prev_pipe_in != -1)
                dup2(prev_pipe_in, STDIN_FILENO);
            
            if (cmd->next)
                dup2(pipe_fd[1], STDOUT_FILENO);

            if (is_builtin)
                exec_builtin(cmd, mini, env);
            else
                exec_command(cmd->command, mini->paths, env);
            
            exit(1);
        }

        if (prev_pipe_in != -1)
            close(prev_pipe_in);
        
        if (cmd->next)
        {
            close(pipe_fd[1]);
            prev_pipe_in = pipe_fd[0];
        }

        cmd = cmd->next;
    }
    while (wait(NULL) > 0);
}