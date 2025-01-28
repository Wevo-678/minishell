/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alribeyr <alribeyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:05:46 by alribeyr          #+#    #+#             */
/*   Updated: 2025/01/28 18:05:49 by alribeyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h" 

int	no_arg(char ***envp)
{
	char	**sorted_env;

	sorted_env = sort_ascii(*envp);
	if (!sorted_env)
		return (1);
	print_env_vars(sorted_env);
	ft_free_array(sorted_env);
	return (0);
}
