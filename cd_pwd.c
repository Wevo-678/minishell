/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabenet <mabenet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 10:43:00 by mabenet           #+#    #+#             */
/*   Updated: 2024/10/16 11:41:40 by mabenet          ###   ########.fr       */
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
    if (!args[1])  // Aucun argument donné, aller dans $HOME
    {
        const char *home = getenv("HOME");
        if (!home)
        {
            printf("cd: HOME not set\n");
            return (1);
        }
        if (chdir(home) != 0)
        {
            perror("cd");
            return (1);
        }
    }
    else if (chdir(args[1]) != 0)  // Essayer de changer vers le répertoire donné
    {
        perror("cd");
        return (1);
    }

    // Mettre à jour la variable PWD dans l'environnement
    return ft_update_pwd(envp);
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
