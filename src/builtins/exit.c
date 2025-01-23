#include "../../includes/minishell.h" 

int	is_numeric(const char *str)
{
	int	i;

	i = 0;
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

void	ft_free(t_main *main_str)
{
	int	i;
	t_node *tmp;

	i = 0;
	while (main_str->path[i])
	{
		free(main_str->path[i]);
		i++;
	}
	free(main_str->path[i]);
	free(main_str->path);
	i = 0;
	while (main_str->env[i])
	{
		free(main_str->env[i]);
		i++;
	}
	free(main_str->env[i]);
	free(main_str->env);
	tmp = main_str->arg_list;
	while (tmp)
	{
		i = 0;
		while (main_str->arg_list->data[i])
		{
			free(main_str->arg_list->data[i]);
			i++;
		}
		free(main_str->arg_list->data[i]);
		free(main_str->arg_list->data);
		tmp = tmp->next;
		free(main_str->arg_list);
		main_str->arg_list = tmp;
	}
	free(main_str->arg_list);
	free(main_str);
	return ;
}

void	ft_free3(t_main *main_str)
{
	int	i;

	i = 0;
	while (main_str->path[i])
	{
		free(main_str->path[i]);
		i++;
	}
	free(main_str->path[i]);
	free(main_str->path);
	i = 0;
	while (main_str->env[i])
	{
		free(main_str->env[i]);
		i++;
	}
	free(main_str->env[i]);
	free(main_str->env);
	free(main_str);
	return ;
}

void	ft_exit(char **args, t_main *main_str)
{
	printf("exit\n");
	if (args[1] == NULL)
	{
		ft_free(main_str);
		exit(0);
	}
	if (is_numeric(args[1]) == 0)
	{
		printf("minishell: exit: %s: numeric argument required\n", args[1]);
		ft_free(main_str);
		exit(2);
	}
	ft_free(main_str);
	exit(atoi(args[1]));
}
