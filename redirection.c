#include "minishell.h"

int    ft_heredoc(char **redirections)
{
    int fd[2];
    char *line;
    line = NULL;
    pipe(fd);
    while(1)
    {
        write(1, "> ", 2);
        line = get_next_line(STDIN_FILENO);
        if(ft_strcmp(line, redirections[1]) == 0)
        {
            free(line);
            break;
        }
        write(fd[1], line, ft_strlen(line));
        write(1, "\n", 1);
        free(line);
    }
    close(fd[1]);
    return(fd[0]);
}

void apply_redirections(char **redirections, t_fd *fds)
{
    for (int i = 0; redirections[i]; i += 2) 
    {
        char *type = redirections[i];
        char *file = redirections[i + 1];

        int fd = 0;
        if (strcmp(type, ">") == 0) {
            fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            fds->stdout = dup(STDOUT_FILENO);
            dup2(fd, STDOUT_FILENO);
        }
        else if (strcmp(type, ">>") == 0)
        {
            fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
            fds->stdout = dup(STDOUT_FILENO);
            dup2(fd, STDOUT_FILENO);
        }
        else if (strcmp(type, "<") == 0)
        {
            fd = open(file, O_RDONLY);
            fds->stdin = dup(STDIN_FILENO);
            dup2(fd, STDIN_FILENO);
        }
        else if (strcmp(type, "<<") == 0)
        {
            (ft_heredoc(redirections));
        }
        close(fd);
    }
}
