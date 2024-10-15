/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picarlie <picarlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:40:26 by picarlie          #+#    #+#             */
/*   Updated: 2024/10/15 18:25:11 by picarlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_node(t_node **first)
{
	t_node	*new;
	t_node	*tmp;

	tmp = *first;
	while (tmp->next)
		tmp = tmp->next;
	new = (t_node *)malloc(sizeof(t_node));
	if (!new)
		return (NULL);
	new->next = NULL;
	tmp->next = new;
}

t_node	**struct_init(void)
{
	t_node	*new;
	
	new = (t_node *)malloc(sizeof(t_node));
	if (!new)
		return (NULL);
	new->next = NULL;
	return (&new);
}

int	main(int argc, char **argv)
{
	t_node	**first;

	
	return (0);
}