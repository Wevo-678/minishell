/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executionv2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picarlie <picarlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:06:27 by picarlie          #+#    #+#             */
/*   Updated: 2025/01/27 17:24:31 by picarlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	lst_wait(void *content)
{
	waitpid(*(int *)content, NULL, 0);
}

int	pid_list_add(t_list **pid_lst, int pid)
{
	int		*content;
	t_list	*new;

	content = ft_calloc(1, sizeof(int));
	if (!content)
		return (1);
	*content = pid;
	new = ft_lstnew(content);
	if (!new)
		return (1);
	if (!*pid_lst)
		*pid_lst = new;
	else
		ft_lstadd_back(pid_lst, new);
	return (0);
}

int	is_builtin(char **args, char ***envp, t_main *main_str)
{
	if (strcmp(args[0], "cd") == 0)
		ft_cd(args, envp);
	else if (strcmp(args[0], "echo") == 0)
		ft_echo(args);
	else if (strcmp(args[0], "pwd") == 0)
		ft_pwd(*envp);
	else if (strcmp(args[0], "export") == 0)
		ft_export(args, envp);
	else if (strcmp(args[0], "unset") == 0)
		ft_unset(args, envp);
	else if (strcmp(args[0], "env") == 0)
		ft_env(*envp);
	else if (strcmp(args[0], "exit") == 0)
	{
		ft_exit(args, main_str);
	}
	else
		return (0);
	return (1);
}

int	return_perror(void)
{
	perror("failed fork");
	return (-1);
}

int	child(t_node *tokens, t_main *main_str, int *redir)
{
	int		pid;
	char	*fullpath;

	pid = fork();
	if (pid < 0)
		return (return_perror());
	else if (pid == 0)
	{
		dup2(redir[0], 0);
		dup2(redir[1], 1);
		if (is_builtin(tokens->data, &main_str->env, main_str))
			exit (0);
		else
		{
			fullpath = pathfinding(main_str, tokens->data[0]);
			if (execve(fullpath, tokens->data, main_str->env) == -1)
			{
				printf("Command not found \n");
				exit(127);
			}
		}
	}
	close(redir[0]);
	close(redir[1]);
	return (pid);
}
