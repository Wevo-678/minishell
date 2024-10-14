/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picarlie <picarlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:06:56 by picarlie          #+#    #+#             */
/*   Updated: 2024/10/14 20:19:58 by picarlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Check if the char str[i] is between quotes */
/* Return 0 if not */
/* Return 1 if opened simple quote before */
/* Return 2 if opened double quote before */
int	between_quotes(char *str, int i)
{
	int	j;
	int	simple_q;
	int	double_q;
	
	j = 0;
	simple_q = 0;
	double_q = 0;
	
	while (j < i)
	{
		if (str[j] == '\'' && !simple_q && !double_q)
			simple_q = 1;
		else if (str[j] == '\'' && simple_q)
			simple_q = 0;
		else if (str[j] == '\"' && !double_q && !simple_q)
			double_q = 2;
		else if (str[j] == '\"' && double_q)
			double_q = 0;
		j++;
	}
	return(simple_q + double_q);
}

/* Check if there is only whitespace from index i */
/* to next pipe or redirection */
/* Return 1 if true */
/* Return 0 if there is other characters */
int	whitespace_cmd(char *str, int i)
{
	int	j;
	
	j = i + 1;
	while (str[j] && str[j] != '<' && str[j] != '>' && str[j] != '|')
	{
		if (str[j] < 9)
			return(0);
		if (str[j] > 13 && str[j] != 32)
			return(0);
		j++;
	}
	return(1);
}

/* Check is there is an empty pipe */
/* Return 1 there is at least one */
/* Return 0 if not */
int	check_empty_pipe(char *input)
{
	int	i;

	if (input[0] == '|')
		return(1);
	i = 0;
	while (input[i])
	{
		if (input[i] == '|' && !between_quotes(input, i))
			if (whitespace_cmd(input, i))
				return(1);
		i++;
	}
	return(0);
}

/* Check is there is an empty redirection */
/* Return 1 there is at least one */
/* Return 0 if not */
int	check_empty_redir(char *input)
{
	int	i;

	if (input[0] == '<' || input[0] == '>')
		return(1);
	i = 0;
	while (input[i])
	{
		if (input[i] == '>' && !between_quotes(input, i))
		{
			if (input[i + 1] == '>')
				i++;
			if (whitespace_cmd(input, i))
				return(1);
		}
		if (input[i] == '<' && !between_quotes(input, i))
		{
			if (input[i + 1] == '<')
				i++;
			if (whitespace_cmd(input, i))
				return(1);
		}
		i++;
	}
	return(0);
}
/*
#include <stdio.h>
int main(int argc, char **argv)
{
	int i;

	i = 0;
	printf("%s\n", argv[1]);
	printf("%d\n", check_empty_redir(argv[1]));
	while (argv[1][i])
	{
		printf("%c\t%d\n",argv[1][i], whitespace_cmd(argv[1], i));
		i++;
	}
	return(0);
}*/