/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picarlie <picarlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:15:44 by picarlie          #+#    #+#             */
/*   Updated: 2025/01/29 15:16:19 by picarlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*delete_quote(char *str)
{
	char	*res;
	char	*tmp;

	tmp = str;
	if ((tmp[0] == '\"' && tmp[ft_strlen(tmp) - 1] == '\"')
		|| (tmp[0] == '\'' && tmp[ft_strlen(tmp) - 1] == '\''))
	{
		res = ft_strdup(++tmp);
		res[ft_strlen(res) - 1] = '\0';
		free(str);
		return (res);
	}
	return (str);
}
