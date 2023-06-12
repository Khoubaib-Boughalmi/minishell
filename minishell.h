/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennatiq <rennatiq@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 14:34:40 by rennatiq          #+#    #+#             */
/*   Updated: 2023/05/12 18:51:31 by rennatiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <stdio.h>
# include <unistd.h>
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# include "./libft/ft_printf/ft_printf.h"

typedef enum s_token_type
{
	AST_COMMAND,
	AST_PIPE,
	AST_REDIRECTION,
}	t_token_type;

typedef enum s_red_type
{
	INPUT,
	APPEND,
	OUTPUT,
	HEREDOC,
	COMMAND,
}	t_red_type;

typedef enum s_red_error
{
	NOERR,
	FILEERR,
	AMBIGUOUSERR,
}	t_red_error;

typedef enum s_trim
{
	NOTRIM,
	TRIM,
}	t_trim;

typedef enum s_ambg
{
	NOAMBG,
	AMBG,
}	t_ambg;

typedef enum s_envp
{
	ENVP,
	EXPORT,
}	t_envp;

typedef struct s_space
{
	int	space_l;
	int	space_r;
}	t_space;

typedef struct s_reder_norm
{
	char	*input;
	char	**str;
	char	*c;
	char	*a;
}	t_reder_norm;

// node structure
typedef struct s_token
{
	t_token_type	type;
	char			**args;
	int				num_args;
	char			*redirect_fd;
	char			*redirect_fname;
	t_red_error		redirect_error;
	t_red_type		red_type;
	int				exit_status;
	int				to_trim;

}	t_token;

typedef struct s_envp_node
{
	struct s_envp_node	*next;
	char				*key;
	char				*value;
}	t_envp_node;

typedef struct s_export
{
	t_envp_node	*export_node;
	t_envp_node	*env_node;
	t_envp_node	*prev_node_export;
	t_envp_node	*prev_node_envp;
}	t_export;

typedef struct s_token_lst
{
	t_token				*token;
	struct s_token_lst	*next;
}	t_token_lst;

typedef struct s_redirection
{
	char				*value;
	t_red_type			type;
	t_red_error			redirect_error;
}	t_redirection;

//shared data goes here
typedef struct s_global_struct
{
	char					*src_input;
	t_token_lst				*tokens_head;
	t_envp_node				*export_head;
	t_envp_node				*envp_head;
	int						exit_status;
	int						sigint_listener;
	char					**list_cmds;
	t_redirection			**list_reds;
	int						stin;
	int						stout;
	int						ppin;
	int						ppout;
}	t_global_struct;

extern t_global_struct	*g_struct;

int				repl(void);
int				tokenize_expand_execute(char *input);
t_token			*tokenize_input(void);
int				init_g_struct(void);
int				init_envp(char **envp);
int				envp_list_vars_len(t_envp_node *ptr);
char			**get_envp_arr(void);
void			free_split(char **list);
t_envp_node		*envp_new_node(char *key, char *value, t_envp envp_val);
void			envp_lst_add_back(t_envp_node *node, t_envp_node **head);
void			envp_delete_node(int pos, t_envp_node **head);
t_envp_node		*envp_find_node(char *key, size_t len, t_envp_node *head);
int				duplicate_list_export(void);
void			ft_env(void);
void			ft_export_with_args(char **phrase);
void			ft_export_no_args(void);
void			ft_unset(char **list_keys);
void			ft_pwd(void);
void			ft_echo(char **list_vars);
void			ft_cd(char **list_vars);
void			ft_exit(char	**list_vars);
void			sig_init(int sig, void (*sig_handler)(int));
void			sigint_hander(int sig);
void			sigquit_hander(int sig);
void			sigint_hander_executor(int sig);
char			*rl_replace_line(const char *text, int clear_undo);
char			**ft_split_string(char const *s, char *list);
int				is_part_of_list(char c, char *list);
t_token_lst		*tokenize(char	*input);
int				ft_check_der(char *str);
int				ft_check_pipe(char *str);

void			expand(t_token_lst *tokens_lst);
void			expand_quotes(char **original);
void			expand_variables(char **original, char *copy, t_trim trim);
void			expand_quotes_red(char **original);
void			expand_variables_redirect(char **original, char	*copy);
int				ft_strlcmp(const char *s1, const char *s2);
int				check_str(char *str);
void			expand_exit_status(char **original, char *copy);
char			**ft_pipe_insert(char *input, char **str);
int				get_variable_len(char *start);
void			cbc_str_join(char **original, char c);
void			create_original_str(char **original);

char			**ft_split_der(char	**str, char n);
void			ft_lst_token_add_back(t_token_lst **lst,
					t_token_lst *new_token);
int				ft_count_str(char	**str);
char			**ft_pipe_insert(char *input, char	**str);
int				ft_count_der(char	**str, char n);

char			*ft_strtrim(char const *s1, char const *set);
char			**ft_split_qotes(char *s, char c);
// int				rl_replace_line(const char *msg, int val);
void			ft_export_with_args_core(char **list_vars,
					t_export export, int i);

int				ft_check_mul_pipe(char	*input, t_token_lst *tokens_lst);
int				ft_check_der(char *str);
int				ft_check_pipe(char *str);
int				ft_check_mul_der(char	*input, char c);
int				ft_check_der_right(char *str);
int				ft_check_der_left(char *str);
char			**ft_der_insert_2(char	*input, char	**str,
					char *c, char *a);
void			ft_free_token(char **str);

char			*path_finder(char *cmd, t_envp_node *envp);
void			cmd_not_found(char **cmd);

char			*create_envp_value(char *key);
void			executor(t_token_lst *token_lst);
char			**create_lst_commands(t_token_lst *token_lst);
t_redirection	**create_lst_redirections(t_token_lst *token_lst);
int				count_commands(t_token_lst *token_lst);
int				count_redirections(t_token_lst *token_lst);
t_token_lst		*ft_put_intoken(char **str);
t_red_type		redtype(char *str);
void			execut_token_norm(char **str, t_redirection **list_reds);
void			free_token_lst(t_token_lst *token_lst);
void			free_cmds_reds_array(char **list_cmds,
					t_redirection **list_reds);

void			ex_main(t_token_lst *token1, t_token_lst *token2);

int				redirect_out_file_heredoc(char *red);
int				redirect_out_file(char *red);
int				redirect_in_file(char *red);
int				redirect_in_file_append(char *red);

void			cmd_not_found(char **cmd);
int				redirect_in_out(t_redirection **list_reds);
int				is_builtin(char	*cmd);
void			handle_builtin(char **list_cmds);
int				list_vars_len(char **list_cmds);
int				char_in_str(char *str, char c);
int				two_d_array_len(char **arr);
char			*trim_str(char *str);
int				ft_cout_red(char *input, char c);
int				syntax_errors(char *input);

void			expand_redirection_fname(t_token *token);
int				expand_redirection_vars(char **original, char *copy);
char			*epur_str(char *str);
char			*join_multiple_args(char **args);
char			*get_key(char *str);
char			*get_value(char *str);
void			ft_export_no_args(void);
void			ft_norm_1(t_export export, char *key, char *value);
void			ft_norm_1_1(t_export export, char *value);
void			ft_norm_2(t_export export, char *key);
void			ft_norm_2_2(t_export export, char *key);
char			*initiate_origin_copy(char **original);
int				check_ambiguous(int vars, char **original);
void			set_ambiguous_state(t_token *token);
int				get_start(char *str);

void			last_cmd_norm(t_redirection **list_reds, char **str);
void			red_out_last(t_redirection **list_reds, int *fd);
void			red_in_last(t_redirection **list_reds, int *fd);
int				is_builtin2(char *cmd);
int				splcount(t_redirection **list_reds);
void			free_args(t_token_lst *token, char **list);
int				is_pipe(t_token_lst *tokens_lst);

#endif
