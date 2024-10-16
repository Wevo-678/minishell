/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabenet <mabenet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 09:56:07 by mabenet           #+#    #+#             */
/*   Updated: 2024/10/16 16:43:30 by mabenet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



// int main(int ac, char **av, char **envp)
// {
//     t_main *main_str;

//     (void)av; // Cela évite le warning de la variable inutilisée

//     // Vérification des arguments
//     if (ac != 1)
//     {
//         printf("Don't need arguments with Minishell\n");
//         return (1);
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



void start_shell(/*t_main *main_str,*/ char **av)
{
    char *input;

    // arg_list = NULL;
    while (1) {
        // Lire la commande utilisateur avec une invite "Minishell$ "
        input = readline("Minishell$ ");
        if (input == NULL || strcmp(input, "exit") == 0)
        {
            free(input);
            break;
        }
        // Ajouter la commande à l'historique
        if (*input)
            add_history(input);
        treat_input(input/*, main_str*/);// premier level de parsing + allocation de la liste chainee
        execute_command(av/*, &main_str->env*/);
        // Libérer la mémoire allouée par readline
        free(input);
    }
}


// main pour tester le parsing des builtin
int main(int ac, char **av, char **envp)
{
    t_main *main_str;
    if (ac == 1)
        return(0);
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

    // Lancer le shell
    start_shell(/*main_str,*/ av);

    // Libérer l'environnement et la structure avant de quitter
    free(main_str->env);
    free(main_str);

    return (0);
}