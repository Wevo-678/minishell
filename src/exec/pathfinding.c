/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alribeyr <alribeyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:10:35 by alribeyr          #+#    #+#             */
/*   Updated: 2025/01/10 17:22:26 by alribeyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*join_path(char *dir, char *command)
{
	size_t	len;
	char	*complete_path;

	if (ft_strncmp(command, "./", 2) == 0 || ft_strncmp(command, "/", 1) == 0)
		return (command);
	else
	{
		len = strlen(dir) + strlen(command) + 2;
		complete_path = malloc(len);
		if (!complete_path)
			return (NULL);
		strcpy(complete_path, dir);
		strcat(complete_path, "/");
		strcat(complete_path, command);
		return (complete_path);
	}
}

char	*pathfinding(t_main *main_str, char *command)
{
	char	*complete_path;
	int		i;
	char	**path;

	complete_path = NULL;
	init_path(get_env_value(main_str->env, "PATH"), &path);
	i = 0;
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
