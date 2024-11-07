#include "../../includes/minishell.h"

/*int	heredoc(char *EOF)
{

}*/

void	make_redir(t_main *main_str, t_node *tokens)
{
	if (tokens->data[0][0] == '<')
	{
		if (tokens->data[0][1] != '<')
		{
			if (main_str->fdin != -1)
				close(main_str->fdin);
			main_str->fdin = open(tokens->data[1], O_RDONLY, 0777);
		}
		/*else
		{
			if (main_str->fdin != -1)
				close(main_str->fdin);
			main_str->fdin = heredoc(tokens->data[1]);
		}*/
	}
	else if (tokens->data[0][0] == '>')
	{
		if (tokens->data[0][1] == '>')
		{
			if (main_str->fdout != -1)
				close(main_str->fdout);
			main_str->fdout = open(tokens->data[1], O_RDWR | O_CREAT | O_TRUNC, 0777);
		}
		else
		{
			if (main_str->fdout != -1)
				close(main_str->fdout);
			main_str->fdout = open(tokens->data[1], O_RDWR | O_CREAT | O_APPEND, 0777);
		}
	}
}

void	redir(t_main *main_str, t_node *tokens)
{
	int		i;
	t_node	*temp;

	while (tokens != NULL)
	{
		printf("%c\n", tokens->data[0][0]);
		if (tokens->data[0][0] == '>' || tokens->data[0][0] == '<')
		{
			make_redir(main_str, tokens);
			if (tokens->data_dup)
				free(tokens->data_dup);
			i = -1;
			while (tokens->data[++i])
				free(tokens->data[i]);
			free(tokens->data);
			if (tokens == main_str->arg_list)
			{
				main_str->arg_list = tokens->next;
				free(tokens);
				tokens = main_str->arg_list;
			}
			else
			{
				temp = main_str->arg_list;
				while (temp->next != tokens)
					temp = temp->next;
				temp->next = tokens->next;
				free(tokens);
				tokens = temp->next;
			}
		}
		else
			tokens = tokens->next;
	}
}
