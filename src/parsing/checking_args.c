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


/*void is_builtin(t_node *tokens, char ***envp, char **path)
{
    execution(path, tokens, *envp);
}*/
