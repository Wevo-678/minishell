#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Fonction pour gérer la redirection de sortie (>)
void handle_output_redirection(const char *filename)
{
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    if (dup2(fd, STDOUT_FILENO) < 0)
    {
        perror("dup2");
        close(fd);
        exit(EXIT_FAILURE);
    }
    close(fd);
}

// Fonction pour gérer la redirection de sortie en ajout (>>)
void handle_append_redirection(const char *filename)
{
    int fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd < 0)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    if (dup2(fd, STDOUT_FILENO) < 0)
    {
        perror("dup2");
        close(fd);
        exit(EXIT_FAILURE);
    }
    close(fd);
}

// Fonction pour gérer la redirection d'entrée (<)
void handle_input_redirection(const char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    if (dup2(fd, STDIN_FILENO) < 0)
    {
        perror("dup2");
        close(fd);
        exit(EXIT_FAILURE);
    }
    close(fd);
}

// Fonction principale pour parser les redirections et exécuter la commande
void execute_command_with_redirections(char *input)
{
    char *args[100]; // Tableau pour stocker les arguments
    int arg_count = 0;
    char *token = strtok(input, " ");
    char *output_file = NULL;
    char *append_file = NULL;
    char *input_file = NULL;

    // Parser les arguments et les redirections
    while (token != NULL)
    {
        if (strcmp(token, ">") == 0)
        {
            token = strtok(NULL, " ");
            if (token)
                output_file = token;
        }
        else if (strcmp(token, ">>") == 0)
        {
            token = strtok(NULL, " ");
            if (token)
                append_file = token;
        }
        else if (strcmp(token, "<") == 0)
        {
            token = strtok(NULL, " ");
            if (token)
                input_file = token;
        }
        else
        {
            args[arg_count++] = token;
        }
        token = strtok(NULL, " ");
    }
    args[arg_count] = NULL;

    // Appliquer les redirections si elles existent
    if (output_file)
        handle_output_redirection(output_file);
    if (append_file)
        handle_append_redirection(append_file);
    if (input_file)
        handle_input_redirection(input_file);

    // Exécuter la commande avec les arguments
    if (execvp(args[0], args) == -1)
    {
        perror("execvp");
        exit(EXIT_FAILURE);
    }
}

int main()
{
    // Exemple de commande avec redirections
    char command[] = "echo \"hello\" >> append.txt";
    execute_command_with_redirections(command);
    return 0;
}
