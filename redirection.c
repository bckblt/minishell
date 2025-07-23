#include "minishell.h"

int ft_heredoc(char **redirections)
{
    int fd[2];
    char *line = NULL;
    char *delimiter = redirections[1];
    
    if (pipe(fd) == -1)
    {
        ft_putstr_fd("minishell: pipe error\n", STDERR_FILENO);
        return (-1);
    }
    while (1)
    {
        line = readline("> ");
        if (!line)
        {
            close(fd[1]);
            close(fd[0]);
            return (-1);
        }
        if (ft_strcmp(line, delimiter) == 0)
        {
            free(line);
            break;
        }
        write(fd[1], line, strlen(line));
        write(fd[1], "\n", 1);
        free(line);
    }
    close(fd[1]);
    return fd[0];
}

void fd_closer(char *file, t_fd *fds, t_list *mini)
{
    (void)file;
    (void)fds;
    ft_putstr_fd("minishell: ", STDERR_FILENO);
    ft_putstr_fd(file, STDERR_FILENO);
    ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
    mini->exit_code = 1;
}

void fd_closer_right(char *file, t_fd *fds, t_list *mini)
{
    (void)file;
    (void)fds;
    ft_putstr_fd("minishell: ", STDERR_FILENO);
    ft_putstr_fd(file, STDERR_FILENO);
    ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
    mini->exit_code = 1;
}

void apply_redirections(char **redirections, t_fd *fds, t_list *mini)
{
    int i = 0;
    char *type;
    char *file;
    
    // Initialize fds if not already done
    if (!fds) 
    {
        mini->exit_code = 1;
        return;
    }
    while (redirections[i]) 
    {
        type = redirections[i];
        file = redirections[i + 1];

        if (ft_strcmp(type, ">") == 0) 
        {
            int fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd == -1)
            {
                fd_closer_right(file, fds, mini);
                return;
            }
            // Save current stdout only if not already saved
            if (fds->stdout == 0)
                fds->stdout = dup(STDOUT_FILENO);
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        else if (ft_strcmp(type, ">>") == 0)
        {
            int fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd == -1)
            {
                fd_closer_right(file, fds, mini);
                return;
            }
            // Save current stdout only if not already saved
            if (fds->stdout == 0)
                fds->stdout = dup(STDOUT_FILENO);
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        else if (ft_strcmp(type, "<") == 0)
        {
            int fd = open(file, O_RDONLY);
            if (fd == -1)
            {
                fd_closer(file, fds, mini);
                return;
            }
            // Save current stdin only if not already saved
            if (fds->stdin == 0)
                fds->stdin = dup(STDIN_FILENO);
            dup2(fd, STDIN_FILENO);
            close(fd);
        }
        i += 2;
    }
}