#include "../../includes/minishell.h"

// Fonction simple pour gérer l'ajout/modification d'une variable d'environnement
int	ft_export(char **args, char ***envp)
{
	int		i;
	char	*name;
	char	*value;
	char	*new_entry;
	size_t	len;

	// Vérification des arguments
	if (!args[1] || !strchr(args[1], '='))
	{
		printf("export: invalid argument\n");
		return (1);
	}

	// Récupérer le nom et la valeur de la variable
	name = ft_strtok(args[1], "=");
	value = ft_strtok(NULL, "=");
	if (!name || !value)
	{
		printf("export: failed to parse name or value\n");
		return (1);
	}

	len = strlen(name);
	i = 0;

	// Parcourir l'environnement pour voir si la variable existe déjà
	while ((*envp)[i])
	{
		if (strncmp((*envp)[i], name, len) == 0 && (*envp)[i][len] == '=')
		{
			free((*envp)[i]);
			new_entry = malloc(strlen(name) + strlen(value) + 2); // +2 pour '=' et '\0'
			if (!new_entry)
			{
				printf("Error: Memory allocation failed for *envp[%d]\n", i);
				return (1);
			}
			sprintf(new_entry, "%s=%s", name, value);
			(*envp)[i] = new_entry;
			printf("Variable updated: %s\n", (*envp)[i]);
			return (0);
		}
		i++;
	}

	// Si la variable n'existe pas, on l'ajoute
	printf("Adding new variable: %s=%s\n", name, value);
	*envp = ft_realloc((void **)(*envp), sizeof(char *) * (i + 1), sizeof(char *) * (i + 2));
	if (!*envp)
	{
		printf("Error: Memory allocation failed for *envp\n");
		return (1);
	}
	new_entry = malloc(strlen(name) + strlen(value) + 2);
	if (!new_entry)
	{
		printf("Error: Memory allocation failed for new_entry\n");
		return (1);
	}
	sprintf(new_entry, "%s=%s", name, value);
	(*envp)[i] = new_entry;
	(*envp)[i + 1] = NULL;
	printf("Variable added: %s\n", (*envp)[i]);
	return (0);
}
