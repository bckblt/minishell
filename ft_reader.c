#include "minishell.h"

void retfd(t_cmd *cmd)
{
    t_fd *fd = cmd->fd;
    if (fd->stdout != 0) {
        dup2(fd->stdout, STDOUT_FILENO);
        close(fd->stdout);
    }
    if (fd->stdin != 0) {
        dup2(fd->stdin, STDIN_FILENO);
        close(fd->stdin);
    }
    if (fd->stderr != 0) {
        dup2(fd->stderr, STDERR_FILENO);
        close(fd->stderr);
    }
}

void exec_builtin(t_cmd *cmd, t_list *mini, char **env)
{
    if (ft_strcmp(cmd->command[0], "cd") == 0)
        ft_cd(cmd->command, mini);
    else if (ft_strcmp(cmd->command[0], "echo") == 0)
        ft_echo(cmd, cmd->quote_num, mini->input, mini);
    else if (ft_strcmp(cmd->command[0], "pwd") == 0)
        ft_pwd(mini);
    else if (ft_strcmp(cmd->command[0], "export") == 0)
        ft_exp(env, cmd, mini);
    else if (ft_strcmp(cmd->command[0], "unset") == 0)
        ft_unset(env, cmd->command[1]);
    else if (ft_strcmp(cmd->command[0], "env") == 0)
        ft_env(env, cmd->command, mini);
    if(cmd->next)
        retfd(cmd);
    exit(mini->exit_code);
}

int heredoc_ctrl(t_cmd *cmd)
{
    if (!cmd->redirections || !cmd->redirections[0])
        return (0);
    if (ft_strcmp(cmd->redirections[0], "<<") == 0)
        return(1);
    return (0);
}

void ft_cmds(t_list *mini, t_cmd *cmd, char **env)
{
    int prev_pipe_in = -1;
    int pipe_fd[2];
    int heredoc_fd = -1;
    pid_t last_pid = -1;

    while (cmd)
    {
        if (cmd->next)
            pipe(pipe_fd);

        if (heredoc_ctrl(cmd))
            heredoc_fd = ft_heredoc(cmd->redirections);

        pid_t pid = fork();
        if (pid == 0)
        {
            if (cmd->redirections && heredoc_fd == -1)
            {
                apply_redirections(cmd->redirections, cmd->fd, mini);
                if (cmd->fd->stdout == -1 || cmd->fd->stdin == -1 || cmd->fd->stderr == -1)
                    exit(mini->exit_code);
            }
            if (prev_pipe_in != -1)
                dup2(prev_pipe_in, STDIN_FILENO);
            if (cmd->next)
                dup2(pipe_fd[1], STDOUT_FILENO);
            if (is_builtin_command(cmd))
                exec_builtin(cmd, mini, env);
            else
                exec_command(cmd->command, mini->paths, env, mini);
            exit(mini->exit_code);
        }
        last_pid = pid;
        if (prev_pipe_in != -1)
            close(prev_pipe_in);
        if (cmd->next)
        {
            close(pipe_fd[1]);
            prev_pipe_in = pipe_fd[0];
        }
        cmd = cmd->next;
    }

    int status;
    pid_t wpid;
    while ((wpid = wait(&status)) > 0)
    {
        if (wpid == last_pid && WIFEXITED(status))
            mini->exit_code = WEXITSTATUS(status);
    }
}
