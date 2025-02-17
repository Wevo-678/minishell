/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picarlie <picarlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:07:51 by picarlie          #+#    #+#             */
/*   Updated: 2025/01/27 14:07:52 by picarlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_print_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}

int	ft_arraylen(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

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

	len = ft_arraylen(array2);
	*array1 = (char **)malloc(sizeof(char *) * (len + 1));
	if (!*array1)
		return (1);
	i = 0;
	while (i < len)
	{
		(*array1)[i] = ft_strdup(array2[i]);
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

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	char	*new_ptr;
	size_t	i;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	i = 0;
	if (ptr)
	{
		while (i < old_size && i < new_size)
		{
			new_ptr[i] = ((char *)ptr)[i];
			i++;
		}
		free(ptr);
	}
	return (new_ptr);
}
