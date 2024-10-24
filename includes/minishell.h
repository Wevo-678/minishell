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

typedef struct s_node
{
    char    *data_dup;
    char    **data;            // Pointeur vers un tableau de chaînes de caractères
    struct  s_node *next;    // Pointeur vers le prochain noeud de la liste
} t_node;

typedef struct s_main
{
    char **env;
    t_node **arg_list;
}   t_main;

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

//env_echo
int	ft_env(char **envp);
int	ft_increment_shlvl(char ***envp);
int	ft_echo(char **args);

//env
char *get_env_value(char **envp, const char *name);
int set_env_value(char ***envp, const char *name, const char *value);
int	copy_value(char *expanded, int j, char **envp, char *var_name);
int	copy_variable(char *expanded, char *input, int *i, char **envp);
char	*expand_variables(char *input, char **envp);

//env_2
void ft_test(char ***env);


//format_check
int	between_quotes(char *str, int i);
int	whitespace_cmd(char *str, int i);
int	check_empty_pipe(char *input);
int	check_empty_redir(char *input);


//main

void start_shell(t_main *main_str);

//num_utils
int	ft_numlen(int n);
char	*ft_itoa(int n);
int	ft_atoi(const char *str);

//split_them_all
t_node	*split_on_pipes(t_node **first_node, char *input);

//count_args
int	pipe_count(char *input);
int	cmd_len(char *input, int i);

//str_utils_two
char **ft_split(char const *s, char c);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s);
int	ft_sprintf(char *buffer, const char *format, ...);

//str_utils
size_t	ft_strlen(const char *str);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strcat(char *dest, const char *src);
char *ft_strncpy(char *dest, const char *src, size_t n);

//struct_init
void	*append_node(t_node **first);
void    *struct_init(t_node **first);

//dup_on_pipes
int	skip_space_last(char *input, int start, int end);
int skip_space_first(char *input, int start, int end);
void	fill_dup(t_node **node, char *input, int start, int end);
void	*str_dup(t_node **first, char *input, int start, int end);
void    *dup_on_pipes(t_node **first, char *input);

//treat_input

void treat_input(char *input, t_main *main_str);
int parse_input(char *input);

//unset_export
char	*ft_strchr(const char *s, int c);
char	*ft_strtok(char *str, const char *delim);
int	ft_unset(char **args, char ***envp);
int	ft_export(char **args, char ***envp);

#endif
