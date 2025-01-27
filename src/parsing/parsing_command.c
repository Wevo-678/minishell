/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picarlie <picarlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:07:28 by picarlie          #+#    #+#             */
/*   Updated: 2025/01/27 14:28:50 by picarlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*delete_quote(char *str)
{
	char	*res;
	char	*tmp;

	tmp = str;
	if ((tmp[0] == '\"' && tmp[ft_strlen(tmp) - 1] == '\"')
		|| (tmp[0] == '\'' && tmp[ft_strlen(tmp) - 1] == '\''))
	{
		res = ft_strdup(++tmp);
		res[ft_strlen(res) - 1] = '\0';
		free(str);
		return (res);
	}
	return (str);
}

char	*expand_env_var(const char *str, int *i, char ***envp)
{
	char	var_name[100];
	char	*env_value;
	int		k;

	k = 0;
	if (str[++(*i)] == '?')
	{
		(*i)++;
		return (ft_itoa(g_signal_pid));
	}
	if (ft_isdigit(str[*i]))
	{
		(*i)++;
		return ("");
	}
	while (str[*i] && (str[*i] == '_' || ft_isalnum(str[*i])) && k < 99)
		var_name[k++] = str[(*i)++];
	var_name[k] = '\0';
	if (var_name[0] != '\0')
	{
		env_value = get_env_value(*envp, var_name);
		if (env_value)
			return (env_value);
	}
	return ("");
}

char	*replace_env_vars(char *str, char ***envp)
{
	char	*result;
	int		i;
	int		j;
	char	*expanded;

	result = malloc(ft_strlen(str) + 1);
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$' && str[i + 1] != '\0' && str[0] != '\'')
		{
			expanded = expand_env_var(str, &i, envp);
			ft_strcpy(&result[j], expanded);
			j += ft_strlen(expanded);
			free(expanded);
		}
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	free(str);
	return (result);
}

void	parsing(t_node **args_list, char ***envp)
{
	int		i;
	t_node	*tmp;

	tmp = (*args_list);
	while (tmp)
	{
		i = 0;
		while (tmp->data[i])
		{
			tmp->data[i] = replace_env_vars(tmp->data[i], envp);
			tmp->data[i] = delete_quote(tmp->data[i]);
			i++;
		}
		tmp = tmp->next;
	}
}
