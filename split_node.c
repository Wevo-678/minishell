/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_&_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabenet <mabenet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:31:06 by mabenet           #+#    #+#             */
/*   Updated: 2024/10/16 15:02:21 by mabenet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char **ft_split(char const *s, char c)
{
    char **result;
    int i = 0, j = 0, k = 0;

    result = malloc(sizeof(char *) * (ft_strlen(s) + 1));  // Allouer de la mémoire pour le résultat
    if (!result)
        return (NULL);
    while (s[i])
    {
        if (s[i] != c)
        {
            j = i;
            while (s[i] != c && s[i] != '\0')
                i++;
            result[k] = malloc(i - j + 1);
            ft_strncpy(result[k], &s[j], i - j);
            result[k++][i - j] = '\0';
        }
        else
            i++;
    }
    result[k] = NULL;
    return (result);
}
