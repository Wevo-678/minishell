#include "../includes/minishell.h"


void	start_shell(t_main *main_str)
{
	char	*input;

	setup_signal_handlers();
    while (1) {
        // Lire la commande utilisateur avec une invite "Minishell$ "
        input = readline("Minishell$ ");
        if (input == NULL)
        {
            printf("exit\n");
            if(ft_strcmp(get_env_value(main_str->env, "SHLVL"), "2") == 0)
                break;
        }
            if (input[0] == '\0')
        {
            free(input);
            continue; // Relancer la boucle sans traiter l'entrée
        }
        // Ajouter la commande à l'historique
        if (*input && (treat_input(input) == 0))
        {
            add_history(input);

            if (!treat_input(input))
            {
                dup_on_pipes(&main_str->arg_list, input);
                split_init(&main_str->arg_list);
				parsing(&main_str->arg_list, &main_str->env);
                execution(main_str->path, main_str->arg_list, main_str->env);
                //free;
            }
        }
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
    ft_increment_shlvl(&main_str->env);
    init_path(get_env_value(envp, "PATH"), &main_str->path);
    
    // Lancer le shell
    start_shell(main_str);

    // Libérer l'environnement et la structure avant de quitter
    free(main_str->env);
    free(main_str);

    return (0);
}
