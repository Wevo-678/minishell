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


int is_builtin(char **args/*, char ***envp*/)
{
    if (strcmp(args[1], "cd") == 0)
        return (1);   // Changer de répertoire
    else if (strcmp(args[1], "echo") == 0)
        return (1);       // Afficher des chaînes
    else if (strcmp(args[1], "pwd") == 0)
        return (1);            // Afficher le chemin actuel
    else if (strcmp(args[1], "export") == 0)
        return (1);  // Ajouter/modifier des variables d'environnement
    else if (strcmp(args[1], "unset") == 0)
        return (1);   // Supprimer des variables d'environnement
    else if (strcmp(args[1], "env") == 0)
        return (1);          // Afficher toutes les variables d'environnement
    // else if (strcmp(args[0], "exit") == 0)
    // {
    //     ft_exit(args);  // Quitter le shell
    //     return (1);     // On retourne 1 pour signaler l'exécution d'un built-in
    // }
    return (0);  // Si ce n'est pas un built-in, on retourne 0
}

void execute_command(char **args/*, char ***envp*/)
{
    if (is_builtin(args))  // Si c'est un built-in, il est exécuté
        return;
    else
    {
        // Si ce n'est pas un built-in, exécuter la commande externe avec execv
        if (execv("/home/mabenet/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin", args) == -1)
            perror("execv");
    }
}