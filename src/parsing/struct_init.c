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
