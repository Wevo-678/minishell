/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabenet <mabenet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 11:06:27 by mabenet           #+#    #+#             */
/*   Updated: 2024/10/14 16:29:27 by mabenet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int parse_input(char *s)
{
	bool	d_quote;
	bool	s_quote;
	int i;

	d_quote = false;
	s_quote = false;
	i = 0;
	while(s[i])
	{
		if(s[i] == '\'' && s_quote == false && d_quote == false)
			s_quote = true;
		else if(s[i] == '\'' && s_quote == true && d_quote == false)
			s_quote = false;
		else if(s[i] == '\"' && s_quote == false && d_quote == false)
			d_quote = true;
		else if(s[i] == '\"' && s_quote == false && d_quote == true)
			d_quote = false;
		i++;
	}
	if (s_quote == false && d_quote == false)
		return(1);
	else 
		return (0);
}

void treat_input(char *input /*t_node *arg_list*/)
{
	// char **tab;
	if (parse_input(input) == 0)
		printf("quote unclosed\n");
		
	// ft_token(input, arg_list);
	// ft_treat_token(arg_list);
}