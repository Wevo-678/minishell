#include "../../includes/minishell.h" 

int	is_numeric(const char *str)
{
	int i = 0;

	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(char **args)
{
	printf("exit\n");

	if (args[1] == NULL)
		exit(0);  // Pas d'argument, on quitte avec code 0

	if (!ft_isdigit(ft_atoi(args[1])))
	{
		printf("minishell: exit: %s: numeric argument required\n", args[1]);
		exit(2);  // Code d'erreur pour argument non numérique
	}
	exit(atoi(args[1]));  // Quitte avec le code de sortie spécifié
}