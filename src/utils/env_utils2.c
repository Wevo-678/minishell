#include "../../includes/minishell.h"

int	count_tokens(const char *str, char delim)
{
	int	count;
	int	in_token;

	count = 0;
	in_token = 0;
	while (*str)
	{
		if (*str == delim)
			in_token = 0;
		else if (!in_token)
		{
			in_token = 1;
			count++;
		}
		str++;
	}
	return (count);
}

void	init_path(char *path, char ***path_tab)
{
	int	count;

	count = count_tokens(path, ':');
	*path_tab = malloc(sizeof(char *) * (count + 1));
	*path_tab = ft_split(path, ':');
}
