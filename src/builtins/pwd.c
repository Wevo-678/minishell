#include "../../includes/minishell.h"

int	ft_pwd(char **env)
{
	if (get_env_value(env, "PWD") != NULL)
	{
		printf("%s\n", get_env_value(env, "PWD"));
		return (0);
	}
	else
	{
		perror("pwd");
		return (1);
	}
}
