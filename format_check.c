/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picarlie <picarlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:06:56 by picarlie          #+#    #+#             */
/*   Updated: 2024/10/14 16:18:38 by picarlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	between_quotes(char **str, int i)
{
	int	j;
	bool simple_q;
	bool double_q;
	
	j = 0;
	simple_q = 0;
	double_q = 0;
	
	while (j < i)
	{
		if (str[j] == '\'')
			if (!simple_q)
				simple_q = TRUE;
			else
				simple_q = FALSE;
		if (str[j] == '\"')
			if (!double_q)
				double_q = TRUE;
			else
				double_q = FALSE;
		j++;
	}
	if (simple_q || double_q)
		return (1);
	if (double_q)
		return()
}

int	check_pipe(char **input)
{
	int	i;
	bool simple_q;
	bool double_q;

	i = 0;
	simple_q = 0;
	double_q = 0;
	
}
