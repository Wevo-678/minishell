#include "../../includes/minishell.h"

char	*get_env_value(char **envp, const char *name)
{
	int	len;
	int	i;

	i = 0;
	len = ft_strlen(name);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return ((envp[i]) + len + 1);
		i++;
	}
	return ("Error dir no find");
}

int	find_and_replace_env(char ***envp, char *new_entry, int len)
{
	int	i;

	i = 0;
	while ((*envp)[i])
	{
		if (ft_strncmp((*envp)[i], new_entry, len) == 0
			&& (*envp)[i][len] == '=')
		{
			free((*envp)[i]);
			(*envp)[i] = new_entry;
			return (1);
		}
		i++;
	}
	return (0);
}

int	set_env_value(char ***envp, const char *name, const char *value)
{
	int		len;
	int		count;
	char	*new_entry;
	char	**new_env;

	len = ft_strlen(name);
	count = ft_arraylen(*envp);
	new_entry = malloc(len + ft_strlen(value) + 2);
	if (!new_entry)
		return (-1);
	ft_strcpy(new_entry, name);
	ft_strcat(ft_strcat(new_entry, "="), value);
	if (find_and_replace_env(envp, new_entry, len))
		return (0);
	new_env = (char **)ft_realloc((void **)*envp, count * sizeof(char *),
			(count + 2) * sizeof(char *));
	if (!new_env)
		return (free(new_entry), -1);
	new_env[count] = new_entry;
	new_env[count + 1] = NULL;
	*envp = new_env;
	return (0);
}
