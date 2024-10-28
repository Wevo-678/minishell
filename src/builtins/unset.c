#include "../../includes/minishell.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}




// ft_strtok fonctionne comme strtok, en coupant les tokens en fonction des délimiteurs
char	*ft_strtok(char *str, const char *delim)
{
	static char *save_ptr;
	char		*start;
	char		*end;

	// Si `str` n'est pas NULL, réinitialiser `save_ptr`
	if (str)
		save_ptr = str;

	// Si `save_ptr` est NULL ou la fin de la chaîne est atteinte, il n'y a plus rien à parser
	if (!save_ptr || *save_ptr == '\0')
		return (NULL);

	// Avancer jusqu'à trouver un caractère qui n'est pas un délimiteur
	start = save_ptr;
	while (*start && ft_strchr(delim, *start))
		start++;

	// Si on atteint la fin de la chaîne après les délimiteurs, retour NULL
	if (*start == '\0')
	{
		save_ptr = NULL;
		return (NULL);
	}

	// Trouver la fin du token
	end = start;
	while (*end && !ft_strchr(delim, *end))
		end++;

	// Terminer le token avec un '\0' si ce n'est pas la fin de la chaîne
	if (*end != '\0')
	{
		*end = '\0';
		save_ptr = end + 1;
	}
	else
		save_ptr = NULL;

	return (start);
}

int	ft_unset(char **args, char ***envp)
{
	int		i, j;
	size_t	len;

	if (!args[1])
		return (1);
	len = ft_strlen(args[1]);
	i = 0;
	while ((*envp)[i])
	{
		if (ft_strncmp((*envp)[i], args[1], len) == 0 && (*envp)[i][len] == '=')
		{
			free((*envp)[i]);
			j = i;
			while ((*envp)[j])
			{
				(*envp)[j] = (*envp)[j + 1];
				j++;
			}
			return (0);
		}
		i++;
	}
	return (0);
}
