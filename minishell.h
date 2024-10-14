/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabenet <mabenet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 08:25:40 by mabenet           #+#    #+#             */
/*   Updated: 2024/10/14 16:27:36 by mabenet          ###   ########.fr       */
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

//main

void start_shell(t_node *arg_list);

//treat_input

void treat_input(char *input /*t_node *arg_list*/);
int parse_input(char *input);

#endif
