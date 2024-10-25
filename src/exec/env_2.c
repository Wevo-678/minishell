#include "../../includes/minishell.h"

void ft_test(char ***env)
{
	char **false_input = malloc(sizeof(char *) * 3) ;

    false_input[0] = "cd";
    false_input[1] = "../minishell/src/parsing";
	false_input[2] = NULL;

	printf("pwd :%s\n", get_env_value(*env, "PWD"));
	ft_cd(false_input, env);
	printf("new pwd :%s\n", get_env_value(*env, "PWD"));
	printf("old pwd:%s\n", get_env_value(*env, "OLDPWD"));

    false_input[0] = "cd";
    false_input[1] = "../../includes";
	false_input[2] = NULL;

	printf("pwd :%s\n", get_env_value(*env, "PWD"));
	ft_cd(false_input, env);
	printf("new pwd :%s\n", get_env_value(*env, "PWD"));
	printf("old pwd:%s\n", get_env_value(*env, "OLDPWD"));

}