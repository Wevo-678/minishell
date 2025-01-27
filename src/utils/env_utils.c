/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabenet <mabenet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:07:55 by picarlie          #+#    #+#             */
/*   Updated: 2025/01/27 16:03:28 by mabenet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_value(char **envp, const char *name)
{
	int	len;
	int	i;

	len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
		{
			return ((envp[i]) + len + 1);
		}
		i++;
	}
	return ("Error dir no find");
}

static char	*create_env_entry(const char *name, const char *value)
{
	char	*new_entry;

	if (!name || !value)
		return (NULL);
	new_entry = malloc(strlen(name) + strlen(value) + 2);
	if (!new_entry)
		return (NULL);
	strcpy(new_entry, name);
	strcat(new_entry, "=");
	strcat(new_entry, value);
	return (new_entry);
}

static int	update_env_value(char **envp, const char *name, char *new_entry)
{
	int	len;
	int	i;

	len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
		{
			free(envp[i]);
			envp[i] = new_entry;
			return (1);
		}
		i++;
	}
	return (0);
}

static int	add_env_entry(char ***envp, char *new_entry)
{
	int		count;
	char	**new_env;

	count = 0;
	while ((*envp)[count])
		count++;
	new_env = realloc(*envp, (count + 2) * sizeof(char *));
	if (!new_env)
	{
		free(new_entry);
		return (-1);
	}
	new_env[count] = new_entry;
	new_env[count + 1] = NULL;
	*envp = new_env;
	return (0);
}

int	set_env_value(char ***envp, const char *name, const char *value)
{
	char	*new_entry;

	if (!envp || !name || !value)
		return (-1);
	new_entry = create_env_entry(name, value);
	if (!new_entry)
		return (-1);
	if (update_env_value(*envp, name, new_entry))
		return (0);
	return (add_env_entry(envp, new_entry));
}
