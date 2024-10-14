/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabenet <mabenet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 09:56:07 by mabenet           #+#    #+#             */
/*   Updated: 2024/10/14 14:51:14 by mabenet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void start_shell(void)
{
    char *input;

    while (1) {
        // Lire la commande utilisateur avec une invite "Minishell$ "
        input = readline("Minishell$ ");
        treat_input(input);// faire le parsing a partir de la
        // Si l'utilisateur entre "exit", quitter le programme
        if (input == NULL || strcmp(input, "exit") == 0) {
            free(input);
            break;
        }

        // Ajouter la commande à l'historique
        if (*input) {
            add_history(input);
        }

        // Afficher la commande entrée (juste pour démonstration)
        printf("Commande : %s\n", input);

        // Libérer la mémoire allouée par readline
        free(input);
    }
}

int main(void)
{
    t_node *arg_list;

    arg_list = NULL;

	// Lancer le shell
	start_shell();

	return 0;
}