#include "../../includes/minishell.h"

int	update_env_var(char *name, char *value, char ***envp, int index)
{
	char	*new_entry;

	new_entry = malloc(strlen(name) + strlen(value) + 2);
	if (!new_entry)
		return (1);
	sprintf(new_entry, "%s=%s", name, value);
	free((*envp)[index]);
	(*envp)[index] = new_entry;
	return (0);
}

int	add_env_var(char *name, char *value, char ***envp, int i)
{
	char	*new_entry;

	new_entry = malloc(strlen(name) + strlen(value) + 2);
	if (!new_entry)
		return (1);
	sprintf(new_entry, "%s=%s", name, value);
	*envp = ft_realloc((void **)(*envp), sizeof(char *) * (i + 1),
			sizeof(char *) * (i + 2));
	if (!*envp)
		return (1);
	(*envp)[i] = new_entry;
	(*envp)[i + 1] = NULL;
	return (0);
}

int	ft_export(char **args, char ***envp)
{
	int		i;
	char	*name;
	char	*value;

	i = 0;
	name = ft_strtok(args[1], "=");
	value = ft_strtok(NULL, "=");
	if (!name || !value)
		return (1);
	while ((*envp)[i])
	{
		if (strncmp((*envp)[i], name, strlen(name)) == 0 &&
				(*envp)[i][strlen(name)] == '=')
			return (update_env_var(name, value, envp, i));
		i++;
	}
	return (add_env_var(name, value, envp, i));
}
