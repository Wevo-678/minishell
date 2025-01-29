/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picarlie <picarlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:15:10 by picarlie          #+#    #+#             */
/*   Updated: 2025/01/29 15:18:03 by picarlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_var_size_ut(char *str, int *total_var_size, int *i, char ***envp)
{
	char	*var_name;
	char	*code_erreur;
	int		k;

	var_name = malloc(sizeof(char) * ft_strlen(str) + 1);
	if (str[*i] == '?')
	{
		code_erreur = ft_itoa(g_signal_pid);
		*total_var_size += ft_strlen(code_erreur);
		free(code_erreur);
		(*i)++;
		return (free(var_name));
	}
	k = 0;
	while (str[*i] && (str[*i] == '_' || ft_isalnum(str[*i])))
		var_name[k++] = str[(*i)++];
	var_name[k] = '\0';
	if (var_name[0] != '\0')
		*total_var_size += ft_strlen(get_env_value_env(*envp, var_name));
	free(var_name);
}

int	check_var_size(char *str, char ***envp)
{
	int		i;
	int		total_var_size;

	total_var_size = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$' && str[i + 1] != '\0' && str[0] != '\'')
		{
			i++;
			check_var_size_ut(str, &total_var_size, &i, envp);
		}
		else
			i++;
	}
	return (total_var_size);
}

char	*expand_env_var(char *str, int *i, char ***envp)
{
	char	*var_name;
	char	*env_value;
	int		k;

	k = 0;
	if (str[++(*i)] == '?')
		return ((*i)++, ft_itoa(g_signal_pid));
	if (ft_isdigit(str[*i]))
		return ((*i)++, ft_strdup(""));
	var_name = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[*i] && (str[*i] == '_' || ft_isalnum(str[*i])))
		var_name[k++] = str[(*i)++];
	var_name[k] = '\0';
	if (var_name[0] != '\0')
	{
		env_value = get_env_value_env(*envp, var_name);
		if (env_value)
			return (free(var_name), ft_strdup(env_value));
	}
	free(var_name);
	return (ft_strdup(""));
}

char	*replace_env_vars(char *str, char ***envp)
{
	char	*result;
	int		i;
	int		j;
	char	*expanded;

	i = 0;
	j = 0;
	result = malloc(sizeof(char) * ft_strlen(str)
			+ check_var_size(str, envp) + 1);
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
