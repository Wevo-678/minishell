/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picarlie <picarlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:08:18 by picarlie          #+#    #+#             */
/*   Updated: 2025/01/27 14:08:19 by picarlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*retstr;

	if (count > 4294967295 || size > 4294967295)
		return (NULL);
	retstr = (void *)malloc(count * size);
	if (!retstr)
		return (NULL);
	ft_bzero(retstr, count * size);
	return (retstr);
}
