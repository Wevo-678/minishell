# include "../../includes/minishell.h"

static void	lst_wait(void *content)
{
	waitpid(*(int *)content, NULL, 0);
}

static int	pid_list_add(t_list **pid_lst, int pid)
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

int	is_builtin(char **args, char ***envp)
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
		ft_exit(args);
	}
	else
	{
		return (0);
	}
	return (1);
}

int	child(t_node *tokens, char **path, char **envp, int *redir)
{
	int		pid;
	char	*fullpath;

	pid = fork();
	if (pid < 0)
	{
		perror("failed fork");
		return (-1);
	}
	else if (pid == 0)
	{
		dup2(redir[0], 0);
		dup2(redir[1], 1);
		if (is_builtin(tokens->data, &envp))
			exit (0);
		else
		{
			fullpath = pathfinding(path, tokens->data[0]);
			execve(fullpath, tokens->data, envp);
			exit (0);
		}
	}
	close(redir[0]);
	close(redir[1]);
	return (pid);
}

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

int	execution(t_main *main_str, t_node *tokens)
{
	int		fd[2];
	int		redir[2];
	t_list	*pidlst;

	setup(main_str, redir, 1);
	pidlst = NULL;
	while (tokens != NULL)
	{
		if (!strcmp(tokens->data[0], "exit"))
		{
			printf("passededant");
			is_builtin(tokens->data, &main_str->env);
		}
		if (ft_pipe(main_str, tokens, fd, redir))
		{
			ft_lstclear(&pidlst, free);
			return (1);
		}
		if (pid_list_add(&pidlst, child(tokens, main_str->path, main_str->env, redir)))
		{
			ft_lstclear(&pidlst, free);
			return (1);
		}
		redir[0] = fd[0];
		tokens = tokens->next;
	}
	ft_lstiter(pidlst, lst_wait);
	ft_lstclear(&pidlst, free);
	setup(main_str, redir, 0);
	return (0);
}
