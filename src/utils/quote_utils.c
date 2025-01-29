/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvalogne <gvalogne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 12:13:37 by gvalogne          #+#    #+#             */
/*   Updated: 2025/01/29 12:23:30 by gvalogne         ###   ########.fr       */
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