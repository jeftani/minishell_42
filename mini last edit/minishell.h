/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeftani <ajeftani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 00:12:21 by gloukas           #+#    #+#             */
/*   Updated: 2023/07/23 14:22:31 by ajeftani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/cdefs.h>
# include <unistd.h>

int						g_exit;

typedef struct s_splity
{
	char				*tab;
	int					i;
	int					count;
	int					j;
	int					start;
	char				**res;
}						t_splity;

typedef struct s_count
{
	int					string;
	int					r_in;
	int					r_out;
	int					r_app;
	int					herd;
	int					end;
}						t_count;

typedef struct s_index
{
	int					string;
	int					r_in;
	int					r_out;
	int					r_app;
	int					herd;
}						t_index;

typedef struct s_cmd
{
	char				**string;
	char **r_in_sig;   // signal in infile
	char **r_in_file;  // here it gives the file name
	char **r_out_sig;  // signal of outfile
	char **r_out_file; // file name of the outfile
	char				**r_app_sig;
	char				**r_app_file;
	char				**herdoc_sig;
	char				**herdoc_lim;
}						t_cmd;

typedef struct s_variables
{
	int					fd;
	int					red;
	int					i;
	int					x;
	int					j;
	int					k;
	int					flag;
}						t_var;

typedef struct s_fd
{
	int					in;
	int					out;
}						t_fd;

typedef struct s_con
{
	int					i;
	int					j;
	int					b;
	int					d;
	char				res[100];
	char				key[200];
	char				*value;
	int					temp;
}						t_con;

typedef struct s_lexer
{
	char				*command;
	t_cmd				*details;
	t_fd				fd;
	struct s_lexer		*next;
}						t_lexer;

typedef struct s_env_elem
{
	char				*key;
	char				*value;
	int					equal;
	struct s_env_elem	*next;
	struct s_env_elem	*prev;
}						t_env_elem;

typedef struct s_env
{
	t_env_elem			*head;
	char				**env;
	t_con				*con;
	int					l;
	int					size;
}						t_env;

//builtins
void					ft_change_dir(char *after, char *before,
							t_env *environment);
char					*search_env_elem1(char *key, char **env);
int						ft_strncmp12(char *s1, char *s2, unsigned int n);
void					ft_execute1(t_env *environment, t_lexer *lexer);
t_env					*createenvironment(char **env);
int						ft_strchr1(char const *s, int c);
char					*ft_substr(char *s, int start, int len);
int						ft_strlen1(const char *str);
char					*ft_strdup(char *str);
char					*ft_strjoin(char *s1, char *s2);
int						ft_strcmp(char *s1, char *s2);
void					built_env(t_env *environment, char **cmd);
void					ft_execute(t_env *environment, char **cmd);
int						export(t_env *environment, char **cmd);
void					pwd(void);
int						ft_is_alpha(int c);
int						ft_isalnum(int c);
char					**ft_split(char *s, char c);
t_env_elem				*new_element(char *line);
char					**creat_double_array_env(t_env *environment);
void					add_env_elem(t_env *env, t_env_elem *new);
void					print_env_sorted(t_env_elem *content);
int						ft_isalpha(int c);
void					unset(t_env *environment, char **cmd);
t_env_elem				*search_env_elem(t_env *env, char *key);
int						echo(char **cmd);
void					exit_f(t_env *environment, char **cmd);
int						ft_isdigit(int c);
void					ft_putstr_fd(char *s, int fd);
int						ft_atoi1(const char *str);
int						cd(t_env *environment, char **cmd);
int						ft_strncmp1(char *s1, char *s2, size_t n);
char					*initial_path(char *path, char **env);
int						ft_error(char *cmd, char *arg, char *msg, int errnum);
void					ft_execute_cmd(t_cmd *cmd, t_env *env);
int						check_builtings(char **cmd);
int						ft_puterr(char *cmd, char *arg, char *msg, int errnum);
int						ft_strchr2(char const *s, int c);
int						ft_puterrfree(char *cmd, char *arg, char *msg,
							int errnum);
void					error_hand(char *str, int n);
int						ft_directerror(char *msg, char *utils);
void					free_paths(char **paths);
void					error_execv(t_lexer *lexer, char **paths);
char					*ft_strchrr(const char *s, int c);
void					another(char **arr, char *cdp, char *cwd,
							t_env *environment);
int						continuous(char *value, char **cmd);
void					ft_cont(char *path, t_con *con, char **env);
void					ft_continue5(char **cmd, t_env *environment);
int						ft_atoi_quote(const char *str);
void					ft_resume(t_env *environment);
char					**forward(t_lexer *lexer);
void					redirect_the_std(t_lexer *lexer);
void					check_it(t_lexer *lexer, int fd[2]);
void					close_it(t_lexer *lexer);
void					check_filed(t_lexer *lexer);
int						dir(char *str);
void					dup_close(t_fd *fd);
void					waitchilds(void);
void					add_var(t_env *environment, char *line);
void					execute_command(t_env *environment, t_lexer *lexer);
void					parent(t_lexer *lexer, int fd[]);
void					ft_maintain(char **cmd, int i, int j,
							t_env *environment);
char					*get_cmd(char **splited, t_lexer *lexer);
void					ft_execute_one(t_env *environment, t_lexer *lexer);
void					case4(t_lexer *lexer, t_var *var);
void					case3(t_lexer *lexer, t_var *var);
void					case2(t_lexer *lexer, t_var *var);
void					ft_link(t_env_elem *newelem, t_env_elem *present);
void					ft_err(char *str, char *message, int c);
char					*search_env_elem2(char *key, char **env , t_env *envi);

//execution
void					ft_redirection(t_lexer *lexer);
int						run_heredoc(t_lexer *lexer, t_env *environment);

//	parse_base.c
int						is_empty(char *cmd_line);
int						check_oper(char c, char *cmd_line, int x);
int						check_pipe(char *cmd_line, char c);
int						check_derec(char *cmd_line);
int						parse(char *cmd_line);

//	parse_special.c
int						is_unclosed_quoate(char *cmd_line);
int						is_valid_closing(int *open_count);
int						check_parenthesis(char *cmd_line);
int						check_braces(char *cmd_line);

//	spaces.c
int						is_inside_quotes(char *str, int pos);
int						is_inside_single_quotes(char *cmd_line, int pos);
int						how_much_outside(char *cmd_line);
void					add_spaces_help(char **cmd_line, char **stock, int i,
							int *j);
void					add_spaces(char **cmd_line);

//	remove_quoates.c
void					delete_quoates_c(char **readPtr, char **writePtr,
							int *i, int *j);
char					**help_quoates(char **cmd);
t_lexer					*delete_quoates_a(t_lexer **lexer);
void					delete_quoates_b(char *string);

// 	split_pipe.c
t_lexer					*create_lexer(char *command);
void					split_pipe_help_a(char *cmd_line, t_splity *s);
void					split_pipe_help_b(char *cmd_line, t_splity *s,
							t_lexer **head);
t_lexer					*split_pipe(char *cmd_line);

//	space_expand.c
char					*get_expanded(char *cmd_line, char *new, int *i,
							t_env *env);
char					*expand(char *cmd_line, t_env *env,t_lexer *lexer);
void					arg_split_help(char *cmd_line, t_splity *s);
char					**arg_split(char *cmd_line);

//	token_help.c
t_count					get_count(char **splited_arr, int i);
t_cmd					*inisia(t_cmd *details);
t_cmd					*creation_a(t_cmd *details, t_count count);
t_cmd					*creation_b(t_cmd *details, t_count count);
t_index					inis_index(void);

//	token.c
char					**remove_empty_element(char *cmd_line);
t_lexer					*function_help_a(t_lexer *head, t_index *index,
							char **splited_arr, int *i);
t_lexer					*function_help_b(t_lexer *head, t_index *index,
							char **splited_arr, int *i);
t_lexer					*get_token(t_lexer **lexer, char *cmd_line);

///	main
void					interruption(int signal);
//+main
#endif
