#include "minishell.h"

int cmd_chk(char *cmd, char **paths) 
{
	if (!cmd || !paths) return 0;

	int i = 0;
	while (paths[i])
	{
		char *path = ft_strjoin(paths[i], "/");
		char *full_path = ft_strjoin(path, cmd);
		free(path);

		if (access(full_path, X_OK) == 0) 
		{
			free(full_path);
			return 1;
		}
		free(full_path);
		i++;
	}
	return 0;
}
int ft_lstsize(t_token *tokens)
{
	int i;
	t_token *tmp;
	tmp = tokens;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return(i);
}

void parse_command(t_cmd **cmd, t_token **tokens) 
{
	int cmd_len = 0, redir_len = 0;
	t_token *tmp = *tokens;

	while (tmp && strcmp(tmp->type, "pipe") != 0)
	{
		if (!strcmp(tmp->type, "word"))
			cmd_len++;
		else if (!strcmp(tmp->type, "rdr"))
			redir_len += 2;
		tmp = tmp->next;
	}
	(*cmd)->command = ft_calloc(cmd_len + 1, sizeof(char *));
	(*cmd)->redirections = ft_calloc(redir_len + 1, sizeof(char *));
	int i = 0, j = 0;
	while (*tokens && strcmp((*tokens)->type, "pipe") != 0) 
	{
		if (!strcmp((*tokens)->type, "word")) 
		{
			if(if_has_dollar((*tokens)->value) && !strcmp((*tokens)->type, "word"))
				(*tokens)->value = exp_dollar((*tokens)->value, (*tokens)->quote_num);
			(*cmd)->command[i++] = ft_strdup((*tokens)->value);
			(*cmd)->quote_num = (*tokens)->quote_num;
			(*tokens) = (*tokens)->next;
		} 
		else if (!strcmp((*tokens)->type, "rdr")) 
		{
			(*cmd)->redirections[j++] = ft_strdup((*tokens)->value);  // ">", "<", vb.
			(*tokens) = (*tokens)->next;
			(*cmd)->redirections[j++] = ft_strdup((*tokens)->value);  // dosya adı
			(*tokens) = (*tokens)->next;
		}
	}
}

t_cmd *ft_parsing(t_token *tokens, t_list *mini) 
{
	(void)mini;
	t_cmd *head = NULL;
	t_cmd **tail = &head;
	while (tokens)
	{
		t_cmd *cmd = ft_calloc(1, sizeof(t_cmd));
		if (!cmd) return NULL;
		
		parse_command(&cmd, &tokens);
		
		*tail = cmd;
		tail = &cmd->next;
		
		if (tokens && !strcmp(tokens->type, "pipe"))
		tokens = tokens->next;
	}
	return head;
}