/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alribeyr <alribeyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:16:07 by alribeyr          #+#    #+#             */
/*   Updated: 2025/01/10 17:16:09 by alribeyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	heredoc(char *strEOF)
{
	int		fd;
	char	*line;

	fd = open(".tmp", O_RDWR | O_CREAT | O_TRUNC, 0777);
	printf("%s\n", strEOF);
	while (1)
	{
		line = readline(">");
		if (!ft_strcmp(line, strEOF))
		{
			close(fd);
			fd = open(".tmp", O_RDONLY, 0777);
			unlink(".tmp");
			free(line);
			return (fd);
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

void	redir_out(t_main *main_str, t_node *tokens, int j)
{
	if (tokens->data[j][1] == '>')
	{
		if (main_str->fdout != -1)
			close(main_str->fdout);
		main_str->fdout = open(tokens->data[j + 1],
				O_RDWR | O_CREAT | O_APPEND, 0777);
	}
	else
	{
		if (main_str->fdout != -1)
			close(main_str->fdout);
		main_str->fdout = open(tokens->data[j + 1],
				O_RDWR | O_CREAT | O_TRUNC, 0777);
	}
}

void	make_redir(t_main *main_str, t_node *tokens, int j)
{
	if (tokens->data[j][0] == '<')
	{
		if (tokens->data[j][1] != '<')
		{
			if (main_str->fdin != -1)
				close(main_str->fdin);
			main_str->fdin = open(tokens->data[j + 1], O_RDONLY, 0777);
		}
		else
		{
			if (main_str->fdin != -1)
				close(main_str->fdin);
			main_str->fdin = heredoc(tokens->data[j + 1]);
		}
	}
	else if (tokens->data[j][0] == '>')
	{
		redir_out(main_str, tokens, j);
	}
}

void	remv_redir(t_node *tokens, int j)
{
	char	**newstr;
	int		i;
	int		z;

	i = 0;
	z = 0;
	while (tokens->data[i])
		i++;
	newstr = (char **)malloc(sizeof(char *) * (i - 1));
	i = 0;
	while (tokens->data[i])
	{
		if (i != j && i != (j + 1))
		{
			newstr[z] = tokens->data[i];
			tokens->data[i] = NULL;
			z++;
		}
		else
			free(tokens->data[i]);
		i++;
	}
	newstr[z] = NULL;
	free(tokens->data);
	tokens->data = newstr;
}

void	redir_cut(t_main *main_str, t_node *tokens)
{
	t_node	*temp;
	int		i;

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

void	redir(t_main *main_str, t_node *tokens)
{
	int		j;

	while (tokens != NULL)
	{
		j = 0;
		while (tokens->data[j])
		{
			if (tokens->data[j][0] == '>' || tokens->data[j][0] == '<')
			{
				if (!tokens->data[j + 1])
				{
					printf("redir without argument\n");
					break ;
				}
				make_redir(main_str, tokens, j);
				if (j == 0 && !tokens->data[j + 2])
					redir_cut(main_str, tokens);
				else
					remv_redir(tokens, j);
				j--;
			}
			j++;
		}
		tokens = tokens->next;
	}
}
