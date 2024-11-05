#include "../../includes/minishell.h"

char	*delete_quote(char *str)
{
	char	*res;

	if ((str[0] == '\"' && str[ft_strlen(str) - 1] == '\"') || (str[0] == '\'' && str[ft_strlen(str) - 1] == '\''))
	{
		res = ft_strdup(++str);
		res[ft_strlen(res) - 1] = '\0';
		return (res);
	}
	return(str);
}

char *replace_env_vars(const char *str, char ***envp)
{
	int	size;
	char *result;
	int i = 0, j = 0;

	size = ft_strlen(str);
	result = malloc(size + 1);
	while (str[i] != '\0')
	{
		if (str[i] == '$' && str[i + 1] != '\0' && str[0] != '\'')
		{
			char var_name[100];
			int k = 0;
			i++;
			while (str[i] && (str[i] == '_' || ft_isalnum(str[i])) && k < 99)
				var_name[k++] = str[i++];
			var_name[k] = '\0';

			char *env_value = get_env_value(*envp, var_name);
			if (env_value && ft_strcmp(env_value,"Error dir not find"))
			{
				result = ft_realloc(result, size, size  + 200);
				size += 200;
				strcpy(&result[j], env_value);
				j += strlen(env_value);
			}
			else
			{
				i -= k + 1;
				result[j++] = str[i++];
			}
		}
		else
		{
			result[j++] = str[i++];
		}
	}
	result[j] = '\0';
	return (result);
}

void	parsing(t_node **args_list, char ***envp)
{
	int	i;
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