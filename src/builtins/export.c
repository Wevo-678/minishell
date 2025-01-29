/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picarlie <picarlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:05:58 by picarlie          #+#    #+#             */
/*   Updated: 2025/01/29 15:10:33 by picarlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	update_env_var(char *name, char *value, char ***envp, int index)
{
	char	*new_entry;

	new_entry = malloc(strlen(name) + strlen(value) + 2);
	if (!new_entry)
		return (1);
	sprintf(new_entry, "%s=%s", name, value);
	free((*envp)[index]);
	(*envp)[index] = new_entry;
	return (0);
}

int	add_env_var(char *name, char *value, char ***envp, int i)
{
	char	*new_entry;

	new_entry = malloc(strlen(name) + strlen(value) + 2);
	if (!new_entry)
		return (1);
	sprintf(new_entry, "%s=%s", name, value);
	*envp = ft_realloc((void **)(*envp), sizeof(char *) * (i + 1),
			sizeof(char *) * (i + 2));
	if (!*envp)
		return (1);
	free((*envp)[i]);
	(*envp)[i] = new_entry;
	(*envp)[i + 1] = NULL;
	return (0);
}

void	print_env_vars(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("declare -x %s\n", envp[i]);
		i++;
	}
}

char	**sort_ascii(char **array)
{
	int		i;
	int		j;
	int		len;
	char	**sorted_array;
	char	*temp;

	len = ft_arraylen(array);
	if (dup_array(&sorted_array, array) != 0)
		return (NULL);
	i = -1;
	while (++i < len - 1)
	{
		j = i + 1;
		while (j < len)
		{
			if (strcmp(sorted_array[i], sorted_array[j]) > 0)
			{
				temp = sorted_array[i];
				sorted_array[i] = sorted_array[j];
				sorted_array[j] = temp;
			}
			j++;
		}
	}
	return (sorted_array);
}

int	ft_export(char **args, char ***envp)
{
	char	*name;
	char	*value;
	int		i;

	i = -1;
	if (!args[1])
		return (no_arg(envp));
	name = ft_strtok(args[1], "=");
	value = ft_strtok(NULL, "=");
	if (!name || !value)
		return (1);
	while ((*envp)[++i])
	{
		if (strncmp((*envp)[i], name, strlen(name)) == 0
				&& (*envp)[i][strlen(name)] == '=')
			return (update_env_var(name, value, envp, i));
	}
	return (add_env_var(name, value, envp, i));
}
