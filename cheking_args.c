/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cheking_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabenet <mabenet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:31:06 by mabenet           #+#    #+#             */
/*   Updated: 2024/10/16 10:32:48 by mabenet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_strcmp(const char *s1, const char *s2)
{
    while (*s1 && (*s1 == *s2) && *s2) // Tant que les deux caractères sont égaux
    {
        s1++;
        s2++;
    }
    return (unsigned char)(*s1) - (unsigned char)(*s2);
}


// int is_build_in(char *cmd)
// {
// 	if (ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "pwd") == 0 ||
// 		ft_strcmp(cmd, "export") == 0 || ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0 ||
// 		ft_strcmp(cmd, "exit") == 0)
// 		return(1);
// 	else
// 		return(0);
// }

// int script_checking(char **script)
// {
// 	if(is_build_in(script[0]) == 1)
// 		check_build_in(**script);
// 	else
// 		// executer avec execve
// }

// void check_build_in(char **script)
// {

// }