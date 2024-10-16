/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabenet <mabenet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 11:06:27 by mabenet           #+#    #+#             */
/*   Updated: 2024/10/16 11:30:25 by mabenet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int unclosed_quote_check(char *s)
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

void treat_input(char *input ,t_main *main_str)
{
	// char **tab;
	if (unclosed_quote_check(input) == 0)
		printf("minishell: unclosed quote error.\n");
	else if (check_empty_pipe(input) == 1 || check_empty_redir(input) == 1)
		printf("minishell: syntax error near unexpected token\n");
	else if(ft_strcmp(input, "env") == 0)
		ft_print_env(main_str->env);
	else if(ft_strcmp(input, "cd") == 0)
		ft_cd(&input ,&main_str->env);
	else if(ft_strcmp(input, "pwd") == 0)
		ft_pwd();


	// ft_token(input, arg_list);
	// ft_treat_token(arg_list);
}