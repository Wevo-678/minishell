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

int is_builtin(char **args, char ***envp)
{
	if (strcmp(args[0], "cd") == 0)
		ft_cd(args, envp);   // Changer de répertoire
	else if (strcmp(args[0], "echo") == 0)
		ft_echo(args);	  // Afficher des chaînes
	else if (strcmp(args[0], "pwd") == 0)
		ft_pwd(*envp);			// Afficher le chemin actuel
	else if (strcmp(args[0], "export") == 0)
		ft_export(args, envp);  // Ajouter/modifier des variables d'environnement
	else if (strcmp(args[0], "unset") == 0)
		ft_unset(args, envp);   // Supprimer des variables d'environnement
	else if (strcmp(args[0], "env") == 0)
		ft_env(*envp);		  // Afficher toutes les variables d'environnement
	else if (strcmp(args[0], "exit") == 0)
	{
		ft_exit(args);// On retourne 1 pour signaler l'exécution d'un built-in
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
		fullpath = pathfinding(path, tokens->data[0]);
		execve(fullpath, tokens->data, envp);
		exit (0);
	}
	close(redir[0]);
	close(redir[1]);
	return (pid);
}

int	execution(char **path, t_node *tokens, char **envp)
{
	int		fd[2];
	int		redir[2];
	int		ogout;
	t_list	*pidlst;

	redir[0] = 0;
	redir[1] = 1;
	pidlst = NULL;
	ogout = dup(1);
	while (tokens != NULL)
	{
		if (is_builtin(tokens->data, &envp))
			return (0);
		if (tokens->next != NULL)
		{
			if (pipe(fd) == -1)
			{
				perror("failed pipe");
				ft_lstclear(&pidlst, free);
				return (1);
			}
		}
		redir[1] = fd[1];
		//if (ft_lstadd_back(&pidlst, ft_lstnew(child(tokens, path, envp))))
		if (pid_list_add(&pidlst, child(tokens, path, envp, redir)))
		{
			ft_lstclear(&pidlst, free);
			return (1);
		}
		redir[0] = fd[0];
		tokens = tokens->next;
	}
	ft_lstiter(pidlst, lst_wait);
	ft_lstclear(&pidlst, free);
	dup2(ogout, 1);
	return (0);
}
