#include "../../includes/minishell.h"

void ft_test(char ***env)
{
	printf("%s\n", get_env_value(*env, "USER"));
	set_env_value(env, "USER", "picarlie");
	printf("%s\n", get_env_value(*env, "USER"));
}