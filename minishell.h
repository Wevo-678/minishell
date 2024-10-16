/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picarlie <picarlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 08:25:40 by mabenet           #+#    #+#             */
/*   Updated: 2024/10/17 20:41:04 by picarlie         ###   ########.fr       */
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

void start_shell(/*t_main *main_str,*/ char **av);

//treat_input

void treat_input(char *input/*, t_main *main_str*/);
int parse_input(char *input);

//format_check
int	between_quotes(char *str, int i);
int	whitespace_cmd(char *str, int i);
int	check_empty_pipe(char *input);
int	check_empty_redir(char *input);

//array_utils
int ft_print_env(char **envp);
int	ft_arraylen(char **array);
void	ft_free_array(char **array);
int	dup_array(char ***array1, char **array2);
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);

//cd_pwd
int	ft_update_pwd(char ***envp);
int ft_cd(char **args, char ***envp);
int	ft_pwd(void);

// checking_args
int ft_strcmp(const char *s1, const char *s2);
void execute_command(char **args/*, char ***envp*/);
int is_builtin(char **args/*, char ***envp*/);

//split_them_all
int	pipe_count(char *input);
t_node	*split_on_pipes(t_node **first_node, char *input);

//str_utils
size_t	ft_strlen(const char *str);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strcat(char *dest, const char *src);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char *ft_strncpy(char *dest, const char *src, size_t n);

//struct_init
void	*append_node(t_node **first);
t_node	**struct_init(t_node **first);

//split&node
char **ft_split(char const *s, char c);


#endif
