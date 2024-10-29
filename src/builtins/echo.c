#include "../../includes/minishell.h"

char *replace_env_vars(const char *str, char ***envp)
{
	int	size;
	char *result;
	int i = 0, j = 0;

	size = ft_strlen(str);
	result = malloc(size + 1);
	while (str[i] != '\0')
	{
		if (str[i] == '$' && str[i + 1] != '\0')
		{
			char var_name[100];
			int k = 0;
			i++;
			while (str[i] && (str[i] == '_' || ft_isalnum(str[i])) && k < 99)
				var_name[k++] = str[i++];
			var_name[k] = '\0';

			char *env_value = get_env_value(*envp, var_name);
			if (env_value && ft_strcmp(env_value,"Error dir no find"))
			{
				result = ft_realloc(result, size, size * 2);
				size *= 2;
				strcpy(&result[j], env_value);
				j += strlen(env_value);
			}
			else
			{
				i -= k + 1;
				result[j++] = str[i++];
			}
		}
		else
		{
			result[j++] = str[i++];
		}
	}
	result[j] = '\0';
	return result;
}

int	ft_echo(char **args, char ***envp)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	while (args[i] && strcmp(args[i], "-n") == 0)
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		char *processed_arg = replace_env_vars(args[i], envp);
		printf("%s", processed_arg);
		free(processed_arg);

		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}
