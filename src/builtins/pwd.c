/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picarlie <picarlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:06:02 by picarlie          #+#    #+#             */
/*   Updated: 2025/01/27 14:06:03 by picarlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(char **env)
{
	if (get_env_value(env, "PWD") != NULL)
	{
		printf("%s\n", get_env_value(env, "PWD"));
		return (0);
	}
	else
	{
		perror("pwd");
		return (1);
	}
}
