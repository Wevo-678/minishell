#include "../../includes/minishell.h"

int	ft_pwd(char **env)
{
	// Buffer pour stocker le répertoire courant
	if (get_env_value(env, "PWD") != NULL) // Obtenir le répertoire courant
	{
		printf("%s\n", get_env_value(env, "PWD")); // print la ligne recuperer
		return (0); // Succès
	}
	else
	{
		perror("pwd"); // Afficher un message d'erreur en cas d'échec
		return (1); // Échec
	}
}
