/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabenet <mabenet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 10:43:00 by mabenet           #+#    #+#             */
/*   Updated: 2024/10/16 16:01:41 by mabenet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

    if (!args[1])  // Aucun argument donné, aller dans $HOME
    {
        home = getenv("HOME");
        if (!home)
        {
            printf("cd: HOME not set\n");
            return (1);
        }
        printf("Trying to change directory to HOME: %s\n", home);  // Debug
        if (chdir(home) != 0)
        {
            perror("cd");
            return (1);
        }
    }
    else
    {
        printf("Trying to change directory to: '%s'\n", args[1]);  // Debug
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
    printf("Updated PWD: %s\n", getenv("PWD"));  // Debug

    return (0);
}

int	ft_pwd(void)
{
	char	cwd[1024];  // Buffer pour stocker le répertoire courant

	if (getcwd(cwd, sizeof(cwd)) != NULL)  // Obtenir le répertoire courant
	{
		printf("%s\n", cwd);  // Afficher le répertoire
		return (0);  // Succès
	}
	else
	{
		perror("pwd");  // Afficher un message d'erreur en cas d'échec
		return (1);  // Échec
	}
}
