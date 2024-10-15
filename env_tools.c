/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabenet <mabenet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:22:35 by mabenet           #+#    #+#             */
/*   Updated: 2024/10/15 18:11:13 by mabenet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_print_env(char **envp)
{
    int i = 0;

    // Parcourt le tableau envp jusqu'à la fin (NULL)
    while (envp[i])
    {
        printf("%s\n", envp[i]); // Affiche chaque variable d'environnement
        i++;
    }
    return 0;
}

int	ft_arraylen(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

#include <stdlib.h>

void	ft_free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	dup_array(char ***array1, char **array2)
{
	int		i;
	int		len;

	if (*array1 != NULL)
		ft_free_array(*array1);
	len = ft_arraylen(array2);
	*array1 = (char **)malloc(sizeof(char *) * (len + 1));
	if (!*array1)
		return (1);
	i = 0;
	while (i < len)
	{
		(*array1)[i] = strdup(array2[i]);
		if (!(*array1)[i])
		{
			ft_free_array(*array1);
			return (1);
		}
		i++;
	}
	(*array1)[i] = NULL;
	return (0);
}
