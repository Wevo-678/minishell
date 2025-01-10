#include "../../includes/minishell.h"

char	*get_env_value(char **envp, const char *name)
{
	int	len;
	int	i;

	len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
		{
			return ((envp[i]) + len + 1);
		}
		i++;
	}
	return ("Error dir no find");
}

int	set_env_value(char ***envp, const char *name, const char *value)
{
	int		len;
	int		count;
	char	**new_env;
	char	*new_entry;
	int		i;

	len = ft_strlen(name);
	i = 0;
	new_entry = malloc(ft_strlen(name) + ft_strlen(value) + 2);
	if (!new_entry)
		return (-1);
	ft_strcpy(new_entry, name);
	ft_strcat(new_entry, "=");
	ft_strcat(new_entry, value);
	while ((*envp)[i])
	{
		if (ft_strncmp((*envp)[i], name, len) == 0 && (*envp)[i][len] == '=')
		{
			free((*envp)[i]);
			(*envp)[i] = new_entry;
			return (0);
		}
		i++;
	}
	count = ft_arraylen(*envp);
	new_env = (char **)ft_realloc((void **)*envp, count * sizeof(char *),
			(count + 2) * sizeof(char *));
	if (!new_env)
	{
		free(new_entry);
		return (-1);
	}
	new_env[count] = new_entry;
	new_env[count + 1] = NULL;
	*envp = new_env;
	return (0);
}
