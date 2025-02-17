/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picarlie <picarlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:09:03 by picarlie          #+#    #+#             */
/*   Updated: 2025/01/27 17:11:15 by picarlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//valgrind --leak-check=full --show-leak-kinds=all
//--suppressions=realine_leak.supp ./minishell

#include "../includes/minishell.h"

pid_t	g_signal_pid;

void	ft_free2(t_main *main_str)
{
	int		i;
	t_node	*tmp;

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

void	full_exec(t_main *main_str, char *input)
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
			if (ft_strcmp(get_env_value(main_str->env, "SHLVL"), "2") == 0)
			{
				ft_free3(main_str);
				exit(0);
			}
		}
		if (input[0] == '\0')
		{
			free(input);
			continue ;
		}
		if (*input && (treat_input(input) == 0))
			full_exec(main_str, input);
		free(input);
	}
}

void	std_init(t_main **main_str)
{
	(*main_str)->stdin = dup(0);
	(*main_str)->stdout = dup(1);
	(*main_str)->fdin = -1;
	(*main_str)->fdout = -1;
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
	std_init(&main_str);
	if (dup_array(&main_str->env, envp) != 0)
	{
		printf("Erreur lors de la copie de l'environnement\n");
		free(main_str);
		return (1);
	}
	ft_increment_shlvl(&main_str->env);
	init_path(get_env_value(envp, "PATH"), &main_str->path);
	start_shell(main_str);
	return (0);
}
