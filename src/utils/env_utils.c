#include "../../includes/minishell.h"


char *get_env_value(char **envp, const char *name)
{
    int len = ft_strlen(name);
    int i = 0;

    while (envp[i])
    {
        // Comparer le nom de la variable avec le début de la chaîne
        if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
        {
            // Retourner la partie après le "="
            return ((envp[i]) + len + 1);
        }
        i++;
    }
    return ("Error dir no find"); // Si la variable n'est pas trouvée
}


int set_env_value(char ***envp, const char *name, const char *value)
{
    int len = ft_strlen(name);
    char *new_entry = malloc(ft_strlen(name) + ft_strlen(value) + 2);
    if (!new_entry)
        return -1;

    // Construire l'entrée de la forme "name=value"
    ft_strcpy(new_entry, name);
    ft_strcat(new_entry, "=");
    ft_strcat(new_entry, value);

    // Chercher si la variable existe déjà
    for (int i = 0; (*envp)[i]; i++)
    {
        if (ft_strncmp((*envp)[i], name, len) == 0 && (*envp)[i][len] == '=')
        {
            free((*envp)[i]);
            (*envp)[i] = new_entry;
            return 0;
        }
    }

    // Si la variable n'existe pas, on l'ajoute à la fin
    int count = ft_arraylen(*envp);
    char **new_env = (char **)ft_realloc((void **)*envp, count * sizeof(char *), (count + 2) * sizeof(char *));
    if (!new_env)
    {
        free(new_entry);
        return -1;
    }

    new_env[count] = new_entry;
    new_env[count + 1] = NULL;
    *envp = new_env;
    return 0;

}

int	copy_value(char *expanded, int j, char **envp, char *var_name)
{
	char	*value;

	value = get_env_value(envp, var_name);
	if (value)
	{
		while (*value)
			expanded[j++] = *value++;
	}
	return (j);
}

int	copy_variable(char *expanded, char *input, int *i, char **envp)
{
	int		start;
	int		j;
	char	var_name[128];

	start = *i + 1;
	(*i)++;
	while (input[*i] && (ft_isalnum(input[*i]) || input[*i] == '_'))
		(*i)++;
	strncpy(var_name, input + start, *i - start);
	var_name[*i - start] = '\0';
	j = copy_value(expanded, strlen(expanded), envp, var_name);
	return (j);
}

char	*expand_variables(char *input, char **envp)
{
	char	*expanded;
	int		i;
	int		j;

	expanded = malloc(1024);
	if (!expanded)
		return (NULL);
	i = 0;
	j = 0;
	while (input[i])
	{
		if (input[i] == '$')
			j = copy_variable(expanded, input, &i, envp);
		else
			expanded[j++] = input[i++];
	}
	expanded[j] = '\0';
	return (expanded);
}
