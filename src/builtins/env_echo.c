#include "../../includes/minishell.h"

int	ft_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}

int	ft_increment_shlvl(char ***envp)
{
	int		i;
	char	*shlvl;
	int		level;
	char	*level_str;
	char	*new_shlvl;

	i = 0;
	while ((*envp)[i])
	{
		if (ft_strncmp((*envp)[i], "SHLVL=", 6) == 0)
		{
			shlvl = &((*envp)[i][6]);
			level = ft_atoi(shlvl) + 1;
			level_str = ft_itoa(level);
			if (!level_str)
				return (1);
			new_shlvl = malloc(ft_strlen("SHLVL=") + ft_strlen(level_str) + 1);
			if (!new_shlvl)
				return (1);
			ft_strcpy(new_shlvl, "SHLVL=");
			ft_strcat(new_shlvl, level_str);
			free(level_str);
			free((*envp)[i]);
			(*envp)[i] = new_shlvl;
			return (0);
		}
		i++;
	}
	*envp = ft_realloc(*envp, sizeof(char *) * (i + 1), sizeof(char *) * (i + 2));
	(*envp)[i] = ft_strdup("SHLVL=1");
	(*envp)[i + 1] = NULL;
	return (0);
}

int	ft_echo(char **args)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (args[1] && strcmp(args[1], "-n") == 0)
	{
		newline = 0;
		i++;
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

