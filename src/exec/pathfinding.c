# include "../../includes/minishell.h"

char *join_path(char *dir, char *command)
{
	if(ft_strncmp(command, "./", 2) == 0 || ft_strncmp(command, "/", 1) == 0)
		return(command);
	else
	{
		size_t len = strlen(dir) + strlen(command) + 2; // +2 pour '/' et '\0'
		char *complete_path = malloc(len);
		if (!complete_path)
			return NULL;

		strcpy(complete_path, dir);
		strcat(complete_path, "/");
		strcat(complete_path, command);
		return complete_path;
	}
}

char *pathfinding(char **path, char *command)
{
	char *complete_path = NULL;
	int i = 0;

	while (path[i])
	{
		complete_path = join_path(path[i], command);
		if (access(complete_path, F_OK | X_OK) == 0)
			return (complete_path);
		free(complete_path);
		i++;
	}
	return (NULL);
}