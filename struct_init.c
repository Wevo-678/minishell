/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabenet <mabenet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:40:26 by picarlie          #+#    #+#             */
/*   Updated: 2024/10/18 13:45:15 by mabenet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "minishell.h"


# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdbool.h>
# include <signal.h>
# include <string.h>
typedef struct s_node
{
    int	test;
    struct s_node *next;
} t_node;

/* Add a node at then end of the LC */
/* Return NULL if malloc fails */
// void	*append_node(t_node **first)
// {
// 	t_node	*new;
// 	t_node	*tmp;

// 	tmp = *first;
// 	while (tmp->next)
// 		tmp = tmp->next;
// 	new = (t_node *)malloc(sizeof(t_node));
// 	if (!new)
// 		return (NULL);
// 	new->next = NULL;
// 	tmp->next = new;
// }
// /* Initialize the first node of the linked chain */
// /* Return NULL if malloc fails */
// void *struct_init(t_node **first)
// {
// 	t_node	*new;
	
// 	new = (t_node *)malloc(sizeof(t_node));
// 	if (!new)
// 		return (NULL);
// 	*first = new;
// 	(*first)->next = NULL;
// }



// #include <stdio.h>
// int	main(int argc, char **argv)
// {
// 	t_node	*first;
// 	t_node	*tmp;

// 	first = struct_init(&first);
// 	append_node(&first);
// 	tmp = first;
// 	while (tmp)
// 	{
// 		printf("%d\n", tmp->test);
// 		tmp = tmp->next;
// 	}
// 	return (0);
// }