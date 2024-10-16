/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabenet <mabenet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 10:47:22 by mabenet           #+#    #+#             */
/*   Updated: 2024/10/16 15:10:49 by mabenet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';  // Ne pas oublier de terminer par un caractère nul
	return (dest);
}

char	*ft_strcat(char *dest, const char *src)
{
	int	i;
	int	j;

	i = 0;
	while (dest[i])  // Avancer jusqu'à la fin de la chaîne `dest`
		i++;
	j = 0;
	while (src[j])  // Ajouter `src` à la suite de `dest`
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';  // Ne pas oublier de terminer par un caractère nul
	return (dest);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}


char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (src[i] && i < n)  // Copier les caractères jusqu'à la limite de n ou la fin de src
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)  // Si la source est plus courte que n, remplir le reste avec des '\0'
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}
