#include "../../includes/minishell.h"

int	ft_echo(char **args)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;

	while (args[i] && args[i][0] == '-' && args[i][1] == 'n')
	{
		int j = 1;
		while (args[i][j] == 'n')
			j++;
		if (args[i][j] == '\0')
		{
			newline = 0;
			i++;
		}
		else
			break;
	}

	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}

	if (newline)
		printf("\n");

	return (0);
}
