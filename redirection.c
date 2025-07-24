#include "minishell.h"

int ft_heredoc(char **redirections, t_list *mini)
{
    int fd[2];
    char *line = NULL;
    char *delimiter = NULL;
    char *expanded_line = NULL;
    int i = 0;

    fd[0] = -1;
    fd[1] = -1;

    while (redirections[i])
    {
        if (strcmp(redirections[i], "<<") == 0 && redirections[i + 1])
        {
            delimiter = redirections[i + 1];

            // Önceki pipe'ı kapat
            if (fd[0] != -1)
                close(fd[0]);
            if (fd[1] != -1)
                close(fd[1]);

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
                    close(fd[0]);
                    close(fd[1]);
                    return -1;
                }
                if (strcmp(line, delimiter) == 0)
                {
                    free(line);
                    break;
                }
                
                // Mevcut exp_dollar fonksiyonunu kullan
                expanded_line = exp_dollar(line, 0, mini);
                
                write(fd[1], expanded_line, strlen(expanded_line));
                write(fd[1], "\n", 1);
                
                if (expanded_line != line)
                    free(expanded_line);
                free(line);
            }
        }
        i++;
    }
    // Sadece son pipe'ın write ucunu kapat, read ucunu return et
    if (fd[1] != -1)
        close(fd[1]);
    return fd[0];
}

// Yardımcı fonksiyon: heredoc için basit dollar expansion
char *expand_heredoc_line(char *line)
{
    if (!if_has_dollar(line))
        return line;
    
    char *result = malloc(1024); // Yeterli buffer
    int i = 0, j = 0;
    
    while (line[i])
    {
        if (line[i] == '$' && line[i + 1])
        {
            if (line[i + 1] == '$')
            {
                // Process ID
                int pid = getpid();
                char pid_str[20];
                sprintf(pid_str, "%d", pid);
                strcpy(result + j, pid_str);
                j += strlen(pid_str);
                i += 2;
            }
            else if (line[i + 1] == '?')
            {
                // Exit code - heredoc'da genelde 0
                result[j++] = '0';
                i += 2;
            }
            else if (ft_isalnum(line[i + 1]) || line[i + 1] == '_')
            {
                // Environment variable
                char env_name[256];
                int k = 0;
                i++; // Skip $
                
                while (line[i] && (ft_isalnum(line[i]) || line[i] == '_'))
                    env_name[k++] = line[i++];
                env_name[k] = '\0';
                
                char *env_value = getenv(env_name);
                if (env_value)
                {
                    strcpy(result + j, env_value);
                    j += strlen(env_value);
                }
            }
            else
            {
                result[j++] = line[i++];
            }
        }
        else
        {
            result[j++] = line[i++];
        }
    }
    result[j] = '\0';
    return result;
}

// Diğer fonksiyonlar aynı kalır...
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