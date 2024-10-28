#include "../../includes/minishell.h"

void ft_test(char ***env, t_main *main_str)
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
	ft_print_env(main_str->path);

}

int count_tokens(const char *str, char delim)
{
    int count;
    int in_token;

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
void init_path(char *path, char ***path_tab)
{
	int count;

	count = count_tokens(path, ':');
	*path_tab = malloc(sizeof(char *) * (count + 1));
	*path_tab = ft_split(path, ':');
}