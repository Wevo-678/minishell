/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picarlie <picarlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:14:17 by picarlie          #+#    #+#             */
/*   Updated: 2025/01/29 15:16:28 by picarlie         ###   ########.fr       */
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
# include <stdarg.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>

extern pid_t	g_signal_pid;

typedef struct s_node
{
	char			*data_dup;
	char			**data;
	struct s_node	*next;
}	t_node;

typedef struct s_main
{
	char	**path;
	char	**env;
	t_node	*arg_list;
	int		stdin;
	int		stdout;
	int		fdin;
	int		fdout;
}	t_main;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

//array_utils
int		ft_print_env(char **envp);
int		ft_arraylen(char **array);
void	ft_free_array(char **array);
int		dup_array(char ***array1, char **array2);
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);

//cd_pwd
int		ft_update_pwd(char ***envp);
int		ft_cd(char **args, char ***envp);
int		ft_pwd(char **env);

// checking_args
int		ft_strcmp(const char *s1, const char *s2);
//void is_builtin(t_node *tokens, char ***envp, char **path);

// parsing_command
void	parsing(t_node **args_list, char ***envp);

//exit
void	ft_free(t_main *main_str);
void	ft_free3(t_main *main_str);
void	ft_exit(char **args, t_main *main_str);

//env_echo
int		ft_env(char **envpm);
int		ft_increment_shlvl(char ***envp);
int		ft_echo(char **args);

//redir2
int		heredoc(char *strEOF);

//execution
void	lst_wait(void *content);
int		pid_list_add(t_list **pid_lst, int pid);
int		is_builtin(char **args, char ***envp, t_main *main_str);
int		child(t_node *tokens, t_main *main_str, int *redir);

//env
char	*get_env_value(char **envp, const char *name);
int		set_env_value(char ***envp, const char *name, const char *value);
int		copy_value(char *expanded, int j, char **envp, char *var_name);
int		copy_variable(char *expanded, char *input, int *i, char **envp);
char	*expand_variables(char *input, char **envp);
void	ft_reduce_shlvl(char ***env);

//env_2
void	ft_test(char ***env, t_main *main_str);
int		count_tokens(const char *str, char delim);
void	init_path(char *path, char ***path_tab);

//env_utils2
char	*get_env_value_env(char **envp, const char *name);

//format_check
int		between_quotes(char *str, int i);
int		whitespace_cmd(char *str, int i);
int		check_empty_pipe(char *input);
int		check_empty_redir(char *input);

//main

void	start_shell(t_main *main_str);

//num_utils
int		ft_numlen(int n);
char	*ft_itoa(int n);
int		ft_atoi(const char *str);

//split_them_all
void	*split_init(t_node **first);

//count_args
int		pipe_count(char *input);
int		count_cmd(char *input);
int		cmd_len(char *input, int i);

//str_utils_two
char	**ft_split(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s);
int		ft_sprintf(char *buffer, const char *format, ...);

//str_utils
size_t	ft_strlen(const char *str);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strcat(char *dest, const char *src);
char	*ft_strncpy(char *dest, const char *src, size_t n);

//quote_utils
char	*delete_quote(char *str);

//struct_init
void	*append_node(t_node **first);
void	*struct_init(t_node **first);

//dup_on_pipes
int		skip_space_last(char *input, int start, int end);
int		skip_space_first(char *input, int start, int end);
void	fill_dup(t_node **node, char *input, int start, int end);
void	*str_dup(t_node **first, char *input, int start, int end);
void	*dup_on_pipes(t_node **first, char *input);

//treat_input

int		treat_input(char *input);
int		parse_input(char *input);

//unset_export
char	*ft_strchr(const char *s, int c);
char	*ft_strtok(char *str, const char *delim);
int		ft_unset(char **args, char ***envp);
int		ft_export(char **args, char ***envp);
int		no_arg(char ***envp);
char	**sort_ascii(char **array);
void	print_env_vars(char **envp);

//utils
int		ft_isalnum(int c);
int		ft_isdigit(int c);

//signal
void	setup_signal_handlers(void);
void	signals(void);

int		execution(t_main *main_str, t_node *tokens);
char	*pathfinding(t_main *main_str, char *command);
void	redir(t_main *main_str, t_node *tokens);
void	*ft_calloc(size_t count, size_t size);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstnew(void *content);
void	ft_bzero(void *s, size_t n);
int		is_valid_export(const char *str);

#endif
