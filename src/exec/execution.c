/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picarlie <picarlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:14:30 by picarlie          #+#    #+#             */
/*   Updated: 2025/01/27 17:34:44 by picarlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	setup(t_main *main_str, int *redir, int start)
{
	if (start)
	{
		if (main_str->fdin == -1)
			redir[0] = 0;
		else
			redir[0] = main_str->fdin;
		if (main_str->fdout != -1)
			dup2(main_str->fdout, 1);
	}
	else
	{
		dup2(main_str->stdin, 0);
		dup2(main_str->stdout, 1);
		main_str->fdin = -1;
		main_str->fdout = -1;
	}
}

int	ft_pipe(t_main *main_str, t_node *tokens, int *fd, int *redir)
{
	if (tokens->next != NULL)
	{
		if (pipe(fd) == -1)
		{
			perror("failed pipe");
			return (1);
		}
		redir[1] = fd[1];
	}
	else
	{
		if (main_str->fdout == -1)
			redir[1] = 1;
		else
			redir[1] = main_str->fdout;
	}
	return (0);
}

void	lst_free(t_list	**pidlst)
{
	ft_lstiter(*pidlst, lst_wait);
	ft_lstclear(pidlst, free);
}

int	return_exec(t_list	**pidlst)
{
	ft_lstclear(pidlst, free);
	return (1);
}

int	execution(t_main *main_str, t_node *tokens)
{
	int		fd[2];
	int		redir[2];
	t_list	*pidlst;

	setup(main_str, redir, 1);
	pidlst = NULL;
	while (tokens != NULL)
	{
		if (!strcmp(tokens->data[0], "exit") || !strcmp(tokens->data[0], "cd")
			|| !strcmp(tokens->data[0], "unset")
			|| !strcmp(tokens->data[0], "export"))
			is_builtin(tokens->data, &main_str->env, main_str);
		else
		{
			if (ft_pipe(main_str, tokens, fd, redir))
				return (return_exec(&pidlst));
			if (pid_list_add(&pidlst, child(tokens, main_str, redir)))
				return (return_exec(&pidlst));
		}
		redir[0] = fd[0];
		tokens = tokens->next;
	}
	lst_free(&pidlst);
	setup(main_str, redir, 0);
	return (0);
}
