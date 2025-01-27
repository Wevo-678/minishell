/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picarlie <picarlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:09:00 by picarlie          #+#    #+#             */
/*   Updated: 2025/01/27 14:09:01 by picarlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_isalnum(int c)
{
	if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	else
		return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int is_valid_export(const char *str)
{
    if (!str || !strchr(str, '='))
        return 0;
    for (int i = 0; str[i] != '='; i++)
    {
        if (i == 0 && !isalpha(str[i]) && str[i] != '_')
            return 0;
        if (!isalnum(str[i]) && str[i] != '_')
            return 0;
    }
    return (1);
}