#include "../../includes/minishell.h"


/* Add a node at then end of the LC */
/* Return NULL if malloc fails */
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
}
/* Initialize the first node of the linked chain */
/* Return NULL if malloc fails */
void *struct_init(t_node **first)
{
	t_node	*new;
	
	new = (t_node *)malloc(sizeof(t_node));
	if (!new)
		return (NULL);
	*first = new;
	(*first)->next = NULL;
}

void	fill_dup(t_node *node, char *input, int start, int end)
{
	int	i;

	i = 0;
	while (i < (end - start))
	{
		node->data[0][i] = input[start + i]; //remove data[0][i]
		printf("%c\n", node->data[0][i]);
		i++;
	}
	node->data[0][i] = 0;//remove data[0][i]
	printf("%s\n", node->data[0]);
}

void	*str_dup(t_node **first, char *input, int start, int end)
{
	t_node	*end_list;

	end_list = (*first);
	if (!start)
	{
		if(!struct_init(first))
			return (NULL);
	}
	else
	{
		if (!append_node(first))
			return (NULL);
		while (end_list->next)
			end_list = end_list->next;
	}
	end_list->data = (char **)malloc(sizeof(char *));//remove data[0][i]
	end_list->data[0] = (char *)malloc(sizeof(char) * (end - start + 1));//remove data[0][i]
	if (!end_list->data)
		return (NULL);
	fill_dup(end_list, input, start, end);
	//return (first);
}

void	*dup_on_pipes(t_node **first, char *input)
{
	t_node	*new;
	int	nb_dup;
	int	nb_pipes;
	int	old_pipe;
	int	i;
	
	i = 0;
	nb_dup = 0;
	nb_pipes = pipe_count(input);
	while (nb_dup <= nb_pipes)
	{
		old_pipe = i;
		while (input[i] && (input[i] != '|' 
				|| (input[i] == '|' && between_quotes(input, i))))
			i++;
		if (!str_dup(first, input, old_pipe, i))
			return (NULL);
		nb_dup++;
	}
	//return (first);
}


#include <stdio.h>
int	main(int argc, char **argv)
{
	t_node	*first;
	t_node	*tmp;

	struct_init(&first);
	dup_on_pipes(&first, argv[1]);
	tmp = first;
	while (tmp)
	{
		//printf("%p\n", tmp);
		printf("%p\n", tmp->data);
		//printf("%c\n", tmp->data[0][0]);
		//printf("%s\n", tmp->data[0]);
		tmp = tmp->next;
	}
	return (0);
}
/*
#include <stdio.h>
int	main(int argc, char **argv)
{
	t_node	*first;
	t_node	*tmp;

	first = struct_init(&first);
	dup
	tmp = first;
	while (tmp)
	{
		printf("%s\n", tmp->data);
		tmp = tmp->next;
	}
	return (0);
}*/