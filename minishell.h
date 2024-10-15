/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabenet <mabenet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 08:25:40 by mabenet           #+#    #+#             */
/*   Updated: 2024/10/15 18:11:26 by mabenet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdbool.h>
# include <signal.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_node
{
    char **data;            // Pointeur vers un tableau de chaînes de caractères
    struct s_node *next;    // Pointeur vers le prochain noeud de la liste
} t_node;

typedef struct s_main
{
    char **env;
    t_node **arg_list;
}   t_main;


//main

void start_shell(t_main *main_str);

//treat_input

void treat_input(char *input, t_main *main_str);
int parse_input(char *input);

//format_check
int	between_quotes(char *str, int i);
int	whitespace_cmd(char *str, int i);
int	check_empty_pipe(char *input);
int	check_empty_redir(char *input);

//env_tools
int ft_print_env(char **envp);
int	ft_arraylen(char **array);
void	ft_free_array(char **array);
int	dup_array(char ***array1, char **array2);

#endif
