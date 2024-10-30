#include "../../includes/minishell.h"

void	ft_switch(t_main *main_str, char **input)
{
	if (ft_strcmp(input[0], "pwd") == 0)
		ft_pwd(main_str->env);
}

char	*join_path(char *dir, char *command)
{
	size_t	len ;
	char	*complete_path;

	len = strlen(dir) + strlen(command) + 2;
	complete_path = malloc(len);
	if (ft_strncmp(command, "./", 2) == 0 || ft_strncmp(command, "/", 1) == 0)
		return (command);
	else
	{
		if (!complete_path)
			return (NULL);
		strcpy(complete_path, dir);
		strcat(complete_path, "/");
		strcat(complete_path, command);
		return (complete_path);
	}
}

// Fonction pour exécuter une commande en utilisant execve
void	execute_command(char **path, char **args, char **envp)
{
	char	*complete_path;
	pid_t	pid;
	int		i;
	int		status;

	i = 0;
	while (path[i])
	{
		complete_path = join_path(path[i++], args[0]);
		pid = fork();
		if (pid == 0)
		{
			execve(complete_path, args, envp);
			free (complete_path);
			exit(EXIT_FAILURE);
		}
		waitpid(pid, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
			return ((void)free(complete_path));
		free(complete_path);
	}
}
