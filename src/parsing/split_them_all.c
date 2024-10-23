
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_them_all.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabenet <mabenet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:32:32 by picarlie          #+#    #+#             */
/*   Updated: 2024/10/16 11:15:48 by mabenet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../../includes/minishell.h"

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
/*
int	ft_strlen_cmd(char **str, int i)
{
	int	j;

	j = 0;
	while(str[i] && str[i] != '|')
	{
		if (!j)
		{
			while (str[i] == ' ' && !between_quotes(str, i))
				i++;
		}
		j++;
		i++;
	}
	return(j);
}

//en cours
int	number_cmd(char *str, int i)
{
	int count_cmd;
	int new_cmd;

	count_cmd = 1;
	new_cmd = 1;
	while (str[i] && str[i] != '|')
	{
		if (str[i] == ' ')
		{
			if (!new_cmd)
			{
				new_cmd++;
				count_cmd++;
			}
			while (str[i] == ' ' && !between_quotes(str, i))
				i++;
		}
		if (str[i] != ' ')
			new_cmd = 0;
		i++;
	}
	return (0);
}
//en cours
t_node	*split_on_pipes(t_node **first, char *input)
{
	int	pcount;
	int	i = 0;

	pcount = pipe_count(input);
	if ((t_node *)struct_init(first) == NULL)
		return (NULL);
	while (i < pcount)
	{
		if (i)
			if ((void *)append_node(first) == NULL)
				return (NULL);
		i++;
	}
	while (i)
	{
		fill_char(first, input);
		i--;
	}
	return(*first);
}
*/