/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabenet <mabenet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 11:06:27 by mabenet           #+#    #+#             */
/*   Updated: 2024/10/14 15:08:50 by mabenet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void treat_input(char *input, t_node arg_list)
{
	char **tab;
	ft_token(input, arg_list);
	ft_treat_token(arg_list);
}