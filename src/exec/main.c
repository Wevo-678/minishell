#include "../../includes/minishell.h"

void start_shell(t_main *main_str)
{
    char *input;

    ft_increment_shlvl(&main_str->env);
    while (1) {
        // Lire la commande utilisateur avec une invite "Minishell$ "
        input = readline("Minishell$ ");
        if (ft_strcmp(input, "./minishell") == 0)
            ft_increment_shlvl(&main_str->env);
        if ((input == NULL || ft_strcmp(input, "exit" ) == 0))
        {
            free(input);
            break;
        }
        // Ajouter la commande à l'historique
        if (*input)
            add_history(input);
        // treat_input(input, main_str);
            
        if(ft_strcmp(input, "test") == 0)
            ft_test(&main_str->env, main_str);
        else
            is_builtin(ft_split(input, ' '),&main_str->env, main_str->path);
        // else if (ft_strcmp(input, "pwd"))
		//     ft_pwd(main_str->env);
        // Libérer la mémoire allouée par readline
        free(input);
    }
}


int main(int ac, char **av, char **envp)
{
    t_main *main_str;

    (void)av; // Cela évite le warning de la variable inutilisée

    // Vérification des arguments
    if (ac != 1)
    {
        printf("Don't need arguments with Minishell\n");
        return (1);
    }

    // Allocation de mémoire pour la structure
    main_str = (t_main *)malloc(sizeof(t_main));
    if (!main_str)
    {
        printf("Erreur d'allocation pour main_str\n");
        return (1);
    }

    // Copie de l'environnement dans la structure main_str->env
    if (dup_array(&main_str->env, envp) != 0)
    {
        printf("Erreur lors de la copie de l'environnement\n");
        free(main_str); // Libérer la structure en cas d'échec
        return (1);
    }
    init_path(get_env_value(envp, "PATH"), &main_str->path);

    // Lancer le shell
    start_shell(main_str);

    // Libérer l'environnement et la structure avant de quitter
    free(main_str->env);
    free(main_str);

    return (0);
}

// main pour tester le parsing des builtin
// int main(int ac, char **av, char **envp)
// {
//     t_main *main_str;
//     (void)av;
    
//     if (ac != 1)
//     {
//         printf("no need argument");
//         return (0);
//     }
//     // Allocation de mémoire pour la structure
//     main_str = (t_main *)malloc(sizeof(t_main));
//     if (!main_str)
//     {
//         printf("Erreur d'allocation pour main_str\n");
//         return (1);
//     }

//     // Copie de l'environnement dans la structure main_str->env
//     if (dup_array(&main_str->env, envp) != 0)
//     {
//         printf("Erreur lors de la copie de l'environnement\n");
//         free(main_str); // Libérer la structure en cas d'échec
//         return (1);
//     }

//     // Lancer le shell
//     start_shell(main_str);

//     // Libérer l'environnement et la structure avant de quitter
//     free(main_str->env);
//     free(main_str);

//     return (0);
// }

// int main(void)
// {
// 	char *env[] = {"PATH=/bin", "USER=test", "SHELL=minishell", NULL};
// 	char **env_copy = NULL;
// 	char *args_export[] = {"export", "NEW_VAR=new_value", NULL};

// 	if (dup_array(&env_copy, env) != 0)
// 	{
// 		printf("Error duplicating array.\n");
// 		return (1);
// 	}

// 	// Test de export
// 	printf("Testing export:\n");
// 	if (ft_export(args_export, &env_copy) != 0)
// 	{
// 		printf("Error executing export\n");
// 		ft_free_array(env_copy);
// 		return (1);
// 	}

// 	// Afficher les éléments de env_copy pour vérifier la mise à jour
// 	for (int i = 0; env_copy[i]; i++)
// 		printf("env_copy[%d]: %s\n", i, env_copy[i]);

// 	// Libérer la mémoire de env_copy
// 	ft_free_array(env_copy);
// 	return (0);
// }

