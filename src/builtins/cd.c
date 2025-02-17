/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picarlie <picarlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:05:43 by picarlie          #+#    #+#             */
/*   Updated: 2025/01/27 14:05:44 by picarlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	free((*envp)[ft_arraylen(*envp)]);
	(*envp)[ft_arraylen(*envp)] = pwd;
	(*envp)[ft_arraylen(*envp) + 1] = NULL;
	return (0);
}

int	ft_cd(char **args, char ***envp)
{
	const char	*home;
	char		*oldpwd;

	oldpwd = get_env_value(*envp, "PWD");
	set_env_value(envp, "OLDPWD", oldpwd);
	if (!args[1])
	{
		home = get_env_value(*envp, "HOME");
		if (!home)
			return (printf("cd: HOME not set\n"), 1);
		if (chdir(home) != 0)
			return (perror("cd"), 1);
	}
	else
	{
		if (chdir(args[1]) != 0)
			return (perror("cd"), 1);
	}
	if (ft_update_pwd(envp) != 0)
		return (printf("Error updating PWD\n"), 1);
	return (0);
}
