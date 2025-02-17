/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picarlie <picarlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:07:43 by picarlie          #+#    #+#             */
/*   Updated: 2025/01/27 14:07:44 by picarlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Add a node at then end of the LC */
/* Return first or NULL if malloc fails */
void	*append_node(t_node **first)
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
	return (first);
}

/* Initialize the first node of the linked chain */
/* Return first or NULL if malloc fails */
void	*struct_init(t_node **first)
{
	t_node	*new;

	new = (t_node *)malloc(sizeof(t_node));
	if (!(new))
		return (NULL);
	(*first) = new;
	(*first)->next = NULL;
	return (first);
}
