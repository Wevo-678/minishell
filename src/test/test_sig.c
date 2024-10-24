#include "../../includes/minishell.h"

// Handler pour SIGINT (Ctrl+C)
void sigint_handler(int signum)
{
    (void)signum; // Supprimer l'avertissement sur l'argument inutilisé
    printf("\n"); // Nouvelle ligne pour l'affichage propre
    rl_on_new_line(); // Informer readline qu'une nouvelle ligne commence
    rl_replace_line("", 0); // Effacer la ligne courante
    rl_redisplay(); // Afficher à nouveau le prompt
}

// Handler pour SIGQUIT (Ctrl+\)
void sigquit_handler(int signum)
{
    (void)signum;
    // Ignorer le signal, ne rien faire
}

void setup_signal_handlers()
{
    signal(SIGINT, sigint_handler); // Assigner le handler pour Ctrl+C
    signal(SIGQUIT, sigquit_handler); // Assigner le handler pour Ctrl+
}

int main()
{
    setup_signal_handlers();
    char *input;

    while (1)
    {
        input = readline("minishell> ");
        if (input == NULL) // Si Ctrl+D est pressé
        {
            printf("exit\n");
            break;
        }
        // Ajout de l'historique readline
        if (*input)
            add_history(input);

        // Simuler l'exécution de la commande
        printf("Commande exécutée: %s\n", input);
        free(input);
    }
    return 0;
}
