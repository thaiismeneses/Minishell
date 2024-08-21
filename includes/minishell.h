/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:24:06 by penascim          #+#    #+#             */
/*   Updated: 2024/08/17 14:00:11 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <unistd.h>
# include <limits.h>

typedef enum e_type
{
	CMD,
	ARG,
	REDIRECT_IN,
	REDIRECT_OUT,
	PIPE,
	HEREDOC,
	APPEND,
	EXPAND,
	ENV_VAR,
	S_QUOTE,
	D_QUOTE,
	COMMAND_SUBSTITUTION,
	NONE,
}						t_type_cmd;

typedef struct s_token
{
	char				*value;
	t_type_cmd			token;
	struct s_token		*next;
	struct s_token		*prev;
}						t_token;

typedef struct s_tree_node
{
	t_type_cmd			type;
	char				*value;
	struct s_tree_node	*left;
	struct s_tree_node	*right;
}						t_tree_node;

typedef struct s_env_node
{
	char				*name_env;
	char				*value_env;
	char				*line_env;
	struct s_env_node	*next;
}						t_env_node;

typedef struct s_main
{
	t_tree_node			*tree;
	t_env_node			*env;
	t_token				*token;
	char				*pwd;
	char				*old_pwd;
}						t_main;

//global
extern int	g_status;

void					print_prompt(t_main *main);

// tokenization
t_token					*tokenization(char *cmd, t_token *data);
int						type_index(t_type_cmd type, char *cmd, int i);
char					*get_token(char *cmd, int i, int start);
t_type_cmd				find_type(char *cmd, int i, int first_token);
int						is_first_token(t_type_cmd type);

// utils_token

t_token					*set_token_list(t_token *data, char *value_cmd,
							int type);
t_token					*get_last_token(t_token *data);
char					*str_join(char *dest, char *src);
char					*join_cmd(char *dest, char *src, int space);

// index
int						index_envvar(char *cmd, int i);
int						index_single(char *cmd, int i);
int						index_double(char *cmd, int i);

// parse
t_tree_node				*parse(t_token *data);
t_tree_node				*parse_command(t_token **data);
t_tree_node				*parse_expression(t_token **data);

// execute
void					ft_free_tab(char **tab);
char					*get_path(char *cmd);
void					print_error_exc(char *msg);
void					ft_execute(char *av, t_env_node *env_list);
void					execute_pipe(t_tree_node *node, t_main *main);
int						execute_cmd(t_tree_node *node, t_main *main);
char					**convert_to_array(t_env_node *env_list);
char					*my_env(char *find, char **envp);

// check_error
int						check_append(t_token *data);
int						check_redirect_out(t_token *data);
int						check_heredoc(t_token *data);
int						check_redirect_in(t_token *data);
int						check_pipe(t_token *data);

// handle_heredoc
void					heredoc(t_token *data);

// utils_errors
int						check_start_end(t_token *data);
int						has_error(t_token *data);

// extra_to_print
void					print_tree(t_tree_node *node, int level);
void					print_token_list(t_token *head);
void					print_env_list(t_env_node *head);
void					print_error(char *msg, char *value);

// check_values
int						is_in_order(t_token *data);
void					swap_nodes(t_token *data);
void					check_values(t_token *data, t_main *main);
char					*concatenate_cmd_tokens(t_token **data);
t_token					*reorganize_cmd(t_token *data);

// free.c
void					free_tree(t_tree_node *node);
void					free_list(t_token **data);
void					free_env_list(t_env_node *head);
void					free_main(t_main *main);

// node.c
void					add_node(t_token **data, t_type_cmd type, char *value);
t_tree_node				*create_tree_node(t_type_cmd type, char *value);

// signal.c
void					mini_signal(void);

// environ.c
t_env_node				*build_environ(char **envp);
void					append_env_node(t_env_node **head, char *line_env);
t_env_node				*create_env_node(const char *env_var);

// builtins.c
void    				exec_cmd(t_main *main);
int 					builtins(char **token, t_main *main);
void					free_matrix(char **matrix);

//exit.c
int						ft_exit(char **token);
int						long_number(char *token);
int						error_exit(char *token, int option);

//env_var.c
int 					ft_env(char **token, t_main *main);

//export.c
int 					ft_export(char **token, t_main *main);
void    				utils_export(char **token, t_main *main, int type);
int    					export_env(char **token, t_main *main);
void					remove_node_export(char *token, t_main *main, int i);

//unset.c
int 					ft_unset(char **token, t_main *main);
void					remove_node_unset(char *token, t_main *main);

//pwd.c
void					start_pwd(t_main *main);

//cd.c
int 					ft_cd(char **token, t_main *main);
void    				update_pwd(t_main *main);

//cd_utils.c
char    				*find_env(t_env_node *env, char *env_name);
int    					home_path(t_main *main);
int    					old_path(t_main *main);
int 					parent_path(t_main *main);

//echo.c
int 					ft_echo(char **token);

#endif
