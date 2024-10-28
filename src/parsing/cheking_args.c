#include "../../includes/minishell.h"

int ft_strcmp(const char *s1, const char *s2)
{
    while (*s1 && (*s1 == *s2) && *s2) // Tant que les deux caractères sont égaux
    {
        s1++;
        s2++;
    }
    return (unsigned char)(*s1) - (unsigned char)(*s2);
}


void is_builtin(char **args, char ***envp, char **path)
{
    if (strcmp(args[0], "cd") == 0)
        ft_cd(args, envp);   // Changer de répertoire
    else if (strcmp(args[0], "echo") == 0)
        ft_echo(args);      // Afficher des chaînes
    else if (strcmp(args[0], "pwd") == 0)
        ft_pwd(*envp);            // Afficher le chemin actuel
    else if (strcmp(args[0], "export") == 0)
        ft_export(args, envp);  // Ajouter/modifier des variables d'environnement
    else if (strcmp(args[0], "unset") == 0)
        ft_unset(args, envp);   // Supprimer des variables d'environnement
    else if (strcmp(args[0], "env") == 0)
        ft_env(*envp);          // Afficher toutes les variables d'environnement
    else if (strcmp(args[0], "exit") == 0)
    {
        ft_exit(args);// On retourne 1 pour signaler l'exécution d'un built-in
    }
    else
        execute_command(path, args, *envp);
}
