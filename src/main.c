//valgrind --leak-check=full --show-leak-kinds=all --suppressions=realine_leak.supp ./minishell

#include "../includes/minishell.h"

pid_t	g_signal_pid;

void	ft_free2(t_main *main_str)
{
	int	i;
	t_node *tmp;

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
	return ;
}

void	start_shell(t_main *main_str)
{
	char	*input;

	signals();
	while (1)
	{
		input = readline("Minishell$ ");
		if (input == NULL)
		{
			printf("exit\n");
			ft_free(main_str);
			if (ft_strcmp(get_env_value(main_str->env, "SHLVL"), "2") == 0)
				break ;
		}
		if (input[0] == '\0')
		{
			free(input);
			continue ;
		}
		if (*input && (treat_input(input) == 0))
		{
			add_history(input);
			if (!treat_input(input))
			{
				dup_on_pipes(&main_str->arg_list, input);
				split_init(&main_str->arg_list);
				parsing(&main_str->arg_list, &main_str->env);
				redir(main_str, main_str->arg_list);
				execution(main_str, main_str->arg_list);
				ft_free2(main_str);
			}
		}
		free(input);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_main	*main_str;

	(void)av;
	if (ac != 1)
	{
		printf("Don't need arguments with Minishell\n");
		return (1);
	}
	main_str = (t_main *)malloc(sizeof(t_main));
	if (!main_str)
	{
		printf("Erreur d'allocation pour main_str\n");
		return (1);
	}
	main_str->stdin = dup(0);
	main_str->stdout = dup(1);
	main_str->fdin = -1;
	main_str->fdout = -1;
	if (dup_array(&main_str->env, envp) != 0)
	{
		printf("Erreur lors de la copie de l'environnement\n");
		free(main_str);
		return (1);
	}
	ft_increment_shlvl(&main_str->env);
	init_path(get_env_value(envp, "PATH"), &main_str->path);
	start_shell(main_str);
	// g_signal_pid = 0;
	// int	i;
	// i = 0;
	// while (main_str->env[i])
	// {
	// 	free(main_str->env[i]);
	// 	i++;
	// }
	// free(main_str->env);
	// free(main_str->path);
	// free(main_str);
	return (0);
}
