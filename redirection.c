#include "minishell.h"

void apply_redirections(char **redirections)
{
    for (int i = 0; redirections[i]; i += 2) 
    {
        char *type = redirections[i];
        char *file = redirections[i + 1];

        int fd = 0;
        if (strcmp(type, ">") == 0) {
            fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            dup2(fd, STDOUT_FILENO);
        } 
        else if (strcmp(type, ">>") == 0) {
            fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
            dup2(fd, STDOUT_FILENO);
        } 
        else if (strcmp(type, "<") == 0) {
            fd = open(file, O_RDONLY);
            dup2(fd, STDIN_FILENO);
        }
        close(fd);
    }
}