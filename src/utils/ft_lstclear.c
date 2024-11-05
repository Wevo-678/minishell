/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziratya <ziratya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:27:07 by alribeyr          #+#    #+#             */
/*   Updated: 2024/11/05 12:36:10 by ziratya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	while (*lst != NULL)
	{
		temp = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = temp;
	}
	lst = NULL;
}

/* Clear the t_node list and its content */
void	clear_list(t_node **first)
{
	t_node	*tmp;
	int		i;

	tmp = (*first);
	while (tmp)
	{
		tmp = (*first)->next;
		i = 0;
		while (tmp->data[i])
		{
			free(tmp->data[i]);
			i++;
		}
		free(tmp->data);
		free(*first);
		(*first) = tmp;
	}
	first = (NULL);
}
