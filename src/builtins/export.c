#include "../../includes/minishell.h"

int update_env_var(char *name, char *value, char ***envp, int index)
{
    char *new_entry = malloc(strlen(name) + strlen(value) + 2);
    if (!new_entry)
        return (1);
    sprintf(new_entry, "%s=%s", name, value);
    free((*envp)[index]);
    (*envp)[index] = new_entry;
    return (0);
}

int add_env_var(char *name, char *value, char ***envp, int i)
{
    char *new_entry = malloc(strlen(name) + strlen(value) + 2);
    if (!new_entry)
        return (1);
    sprintf(new_entry, "%s=%s", name, value);
    *envp = ft_realloc((void **)(*envp), sizeof(char *) * (i + 1), sizeof(char *) * (i + 2));
    if (!*envp)
        return (1);
    (*envp)[i] = new_entry;
    (*envp)[i + 1] = NULL;
    return (0);
}

void print_env_vars(char **envp)
{
    int i = 0;

    while (envp[i])
    {
        printf("declare -x %s\n", envp[i]);
        i++;
    }
}

char	**sort_ascii(char **array)
{
	int		i;
	int		j;
	int		len;
	char	**sorted_array;
	char	*temp;

	len = ft_arraylen(array);
	sorted_array = malloc(sizeof(char *) * (len + 1));
	if (!sorted_array || dup_array(&sorted_array, array) != 0)
		return (NULL);

	i = 0;
	while (i < len - 1)
	{
		j = i + 1;
		while (j < len)
		{
			if (strcmp(sorted_array[i], sorted_array[j]) > 0)
			{
				temp = sorted_array[i];
				sorted_array[i] = sorted_array[j];
				sorted_array[j] = temp;
			}
			j++;
		}
		i++;
	}
	return (sorted_array);
}

int ft_export(char **args, char ***envp)
{
    char	**sorted_env;
	int		i;

    i = 0;
    if (!args[1])
    {
		sorted_env = sort_ascii(*envp);
		if (!sorted_env)
			return (1);
		print_env_vars(sorted_env);
		ft_free_array(sorted_env);
		return (0);
    }
    char *name = ft_strtok(args[1], "=");
    char *value = ft_strtok(NULL, "=");
    if (!name || !value)
        return (1);

    while ((*envp)[i])
    {
        if (strncmp((*envp)[i], name, strlen(name)) == 0 && (*envp)[i][strlen(name)] == '=')
            return update_env_var(name, value, envp, i);
        i++;
    }
    return add_env_var(name, value, envp, i);
}

