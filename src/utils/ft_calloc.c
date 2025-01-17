/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziratya <ziratya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 15:24:45 by aribeyre          #+#    #+#             */
/*   Updated: 2024/11/04 18:25:30 by ziratya          ###   ########.fr       */
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
