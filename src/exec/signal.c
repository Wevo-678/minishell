#include "../../includes/minishell.h"

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