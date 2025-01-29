/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picarlie <picarlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:14:37 by picarlie          #+#    #+#             */
/*   Updated: 2025/01/29 15:14:41 by picarlie         ###   ########.fr       */
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
