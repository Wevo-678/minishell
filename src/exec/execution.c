# include "../../includes/minishell.h"

void ft_switch(t_main *main_str, char **input)
{
    if (ft_strcmp(input[0], "pwd") == 0)
        ft_pwd(main_str->env);
    
    
}

char *join_path(char *dir, char *command)
{
    if(ft_strncmp(command, "./", 2) == 0 || ft_strncmp(command, "/", 1) == 0)
        return(command);
    else
    {
        size_t len = strlen(dir) + strlen(command) + 2; // +2 pour '/' et '\0'
        char *complete_path = malloc(len);
        if (!complete_path)
            return NULL;

        strcpy(complete_path, dir);
        strcat(complete_path, "/");
        strcat(complete_path, command);
        return complete_path;
    }
}
// Fonction pour exécuter une commande en utilisant execve
void execute_command(char **path, char **args, char **envp)
{
    char *complete_path = NULL;
    pid_t pid;
    int i = 0;

    while (path[i])
    {
        // Concaténer le chemin avec la commande
        complete_path = join_path(path[i], args[0]);
        if (!complete_path)
        {
            perror("Erreur d'allocation");
            return;
        }

        pid = fork();
        if (pid < 0)
        {
            perror("Erreur de fork");
            free(complete_path);
            return;
        }
        if (pid == 0)
        {
            // Processus enfant
            if (execve(complete_path, args, envp) == -1)
            {
                free(complete_path); // Libérer et essayer le chemin suivant
                exit(EXIT_FAILURE);  // Quitter le processus enfant en cas d'erreur
            }
        }
        else
        {
            // Processus parent attend pour vérifier le succès
            int status;
            waitpid(pid, &status, 0);
            if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
            {
                printf("Commande exécutée avec succès : %s\n", complete_path);
                free(complete_path);
                return;  // Sortir si execve réussit
            }
        }

        free(complete_path);
        i++;
    }
}

    // Si aucun chemin n'est valide
