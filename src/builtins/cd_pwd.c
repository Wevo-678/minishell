#include "../../includes/minishell.h"

int	ft_find_env(char ***envp, char *pwd)
{
	int	i;

	i = 0;
	while ((*envp)[i])
	{
		if (ft_strncmp((*envp)[i], "PWD=", 4) == 0)
		{
			free((*envp)[i]);
			(*envp)[i] = pwd;
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_update_pwd(char ***envp)
{
	char	cwd[1024];
	char	*pwd;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (1);
	pwd = malloc(ft_strlen("PWD=") + ft_strlen(cwd) + 1);
	if (!pwd)
		return (1);
	ft_strcpy(pwd, "PWD=");
	ft_strcat(pwd, cwd);
	if (ft_find_env(envp, pwd))
		return (0);
	*envp = ft_realloc(*envp, sizeof(char *) * (ft_arraylen(*envp) + 1),
			sizeof(char *) * (ft_arraylen(*envp) + 2));
	if (!*envp)
		return (1);
	(*envp)[ft_arraylen(*envp)] = pwd;
	(*envp)[ft_arraylen(*envp) + 1] = NULL;
	return (0);
}


int ft_cd(char **args, char ***envp)
{
 const char *home;
 char *oldpwd; 
	oldpwd = get_env_value(*envp, "PWD");
	set_env_value(envp, "OLDPWD", oldpwd);
	
    if (!args[1])  // Aucun argument donné, aller dans $HOME
    {
        home = get_env_value(*envp, "HOME");
        if (!home)
        {
            printf("cd: HOME not set\n");
            return (1);
        }
        // printf("Trying to change directory to HOME: %s\n", home);  // Debug
        if (chdir(home) != 0)
        {
            perror("cd");
            return (1);
        }
    }
    else
    {
        // printf("Trying to change directory to: '%s'\n", args[1]);  // Debug
        if (chdir(args[1]) != 0)  // Essayer de changer vers le répertoire donné
        {
            perror("cd");
            return (1);
        }
    }

    // Vérifier si le répertoire a bien changé et mettre à jour PWD
    if (ft_update_pwd(envp) != 0)
    {
        printf("Error updating PWD\n");
        return (1);
    }
    // printf("Updated PWD: %s\n", getenv("PWD"));  // Debug

    return (0);
}

int	ft_pwd(char **env)
{
	  // Buffer pour stocker le répertoire courant

	if (get_env_value(env, "PWD") != NULL)  // Obtenir le répertoire courant
	{
		printf("%s\n", get_env_value(env, "PWD"));  // print la ligne recuperer
		return (0);  // Succès
	}
	else
	{
		perror("pwd");  // Afficher un message d'erreur en cas d'échec
		return (1);  // Échec
	}
}
