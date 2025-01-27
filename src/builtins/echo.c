/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picarlie <picarlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:05:47 by picarlie          #+#    #+#             */
/*   Updated: 2025/01/27 14:05:48 by picarlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	args_n(char **args, int *newline, int *j, int *i)
{
	while (args[*i] && args[*i][0] == '-' && args[*i][1] == 'n')
	{
		*j = 1;
		while (args[*i][*j] == 'n')
			(*j)++;
		if (args[*i][*j] == '\0')
		{
			*newline = 0;
			(*i)++;
		}
		else
			break ;
	}
}

int	ft_echo(char **args)
{
	int	i;
	int	j;
	int	newline;

	i = 1;
	j = 0;
	newline = 1;
	args_n(args, &newline, &j, &i);
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}
