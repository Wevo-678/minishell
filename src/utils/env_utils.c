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

