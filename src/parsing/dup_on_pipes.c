#include "../../includes/minishell.h"

/* Check if there is only spaces from start to EOF or next pipe */
/* Return 1 if true, return 0 if not */
int	skip_space_last(char *input, int start, int end)
{
	while (input[start] && input[start] == ' ')
	{
		start++;
	}
	if (start == end || !input[start])
		return (1);
	return (0);
}

/* Skip all the spaces at the beginning of the string */
/* Return the real start position */
int	skip_space_first(char *input, int start, int end)
{
	while (input[start] && input[start] == ' ' && (start < end - 1)
		&& !between_quotes(input, start))
		start++;
	return (start);
}

/* Fill a node with the input between two pipes */
void	fill_dup(t_node **node, char *input, int start, int end)
{
	int		i;
	t_node	*tmp;

	i = 0;
	tmp = (*node);
	while (i < (end - start))
	{
		if (!i)
			start = skip_space_first(input, start, end);
		else
		{
			if (skip_space_last(input, start + i, end))
			{
				tmp->data_dup[i] = 0;
				break ;
			}
		}
		tmp->data_dup[i] = input[start + i];
		i++;
	}
	tmp->data_dup[i] = 0;
}

/* Malloc all the nodes */
/* Call the fill function */
/* Return first or NULL if malloc fails */
void	*str_dup(t_node **first, char *input, int start, int end)
{
	t_node	*end_list;

	if (!start)
	{
		if (!struct_init(first))
			return (NULL);
		end_list = (*first);
	}
	else
	{
		end_list = (*first);
		if (!append_node(first))
			return (NULL);
		while (end_list->next)
			end_list = end_list->next;
	}
	end_list->data_dup = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!end_list->data_dup)
		return (NULL);
	fill_dup(&end_list, input, start, end);
	return (first);
}

/* Count the number of nodes needed */
/* Call the dup function */
/* Return first or NULL if malloc fails */
void	*dup_on_pipes(t_node **first, char *input)
{
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
		i++;
	}
	return (first);
}

/*
#include <stdio.h>
int	main(int argc, char **argv)
{
	t_node	*first;
	t_node	*tmp;

	dup_on_pipes(&first, argv[1]);
	tmp = first;
	while (tmp)
	{
		printf("%s\n", tmp->data_dup);
		tmp = tmp->next;
	}
	return (0);
}*/
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