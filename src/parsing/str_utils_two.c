#include "../../includes/minishell.h"


char **ft_split(char const *s, char c)
{
    char **result;
    int i = 0, j = 0, k = 0;

    result = malloc(sizeof(char *) * (ft_strlen(s) + 1));  // Allouer de la mémoire pour le résultat
    if (!result)
        return (NULL);
    while (s[i])
    {
        if (s[i] != c)
        {
            j = i;
            while (s[i] != c && s[i] != '\0')
                i++;
            result[k] = malloc(i - j + 1);
            ft_strncpy(result[k], &s[j], i - j);
            result[k++][i - j] = '\0';
        }
        else
            i++;
    }
    result[k] = NULL;
    return (result);
}


int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	i;

	dup = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

int	ft_sprintf(char *buffer, const char *format, ...)
{
	va_list	args;
	int		i;
	int		j;
	char	*str;

	va_start(args, format);
	i = 0;
	j = 0;
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1] == 's' && i++)
		{
			str = va_arg(args, char *);
			while (*str)
				buffer[j++] = *str++;
		}
		else if (format[i] == '%' && format[i + 1] == 'd' && i++)
		{
			str = ft_itoa(va_arg(args, int));
			if (!str)
				return (-1);
			while (*str)
				buffer[j++] = *str++;
			free(str);
		}
		else
			buffer[j++] = format[i];
		i++;
	}
	buffer[j] = '\0';
	va_end(args);
	return (j);
}


