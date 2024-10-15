/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_them_all.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picarlie <picarlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:32:32 by picarlie          #+#    #+#             */
/*   Updated: 2024/10/15 17:40:40 by picarlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/* Return the number of pipes in the string */
int	pipe_count(char *input)
{
	int	i;
	int	pcount;

	i = 0;
	pcount = 0;
	while (input[i])
	{
		if (input[i] == '|')
			if (!between_quotes(input, i))
				pcount++;
		i++;
	}
	return (pcount);
}

t_node	*split_on_pipes(t_node **first_node, char *input)
{
	t_node	*new_node;
	t_node	*tmp;
	
	new_node = (t_node *)malloc(sizeof(t_node));
	if (!new_node)
		return (NULL);
	*first_node = new_node;
	new_node->next = NULL;
	return();
}

/*
int	ft_strlen_cmd(char *str, int i)
{
	int	j;
	int	white_count;

	j = 0;
	while(str[i] && str[i] != '|')
	{
		if (str[i] == ' ')
			white_count++;
		if (str[i] >= 9 && str[i] <= 13)
			white_count++;
		j++;
		i++;
	}
	return(j);
}*/