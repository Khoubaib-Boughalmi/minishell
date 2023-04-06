# ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <unistd.h>
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# include	"./libft/ft_printf/ft_printf.h"

// AST node types
typedef enum
{
	AST_COMMAND,     // a command to execute
	AST_PIPE,        // a pipe between two commands
	AST_REDIRECTION, // a redirection of input or output
} t_token_type;


typedef enum
{
	INPUT,
	APPEND,
	OUTPUT,
	HEREDOC,
	COMMAND,
} t_red_type;

// node structure
typedef struct s_token
{
	t_token_type	type; // the type of the token
	char			**args; // the arguments for a command token
	int				num_args; // the number of arguments for a command token
	char			*redirect_fd; // the file descriptor to redirect for a redirection token
	char			*redirect_fname; // the filename to redirect to for a redirection token
	t_red_type		red_type;
	int				exit_status;
} t_token;


typedef struct s_envp_node
{
	struct s_envp_node	*next;
	char				*key;
	char				*value;
} t_envp_node;

typedef struct s_token_lst
{
	t_token				*token;
	struct s_token_lst *next;
} t_token_lst;

typedef struct s_redirection
{
	char						*value;
	t_red_type					type;
} t_redirection;

//shared data goes here
typedef struct s_global_struct
{
	char					*src_input;		//pointer to the users source input
	t_token_lst				*tokens_head;	//linked list of tokens
	t_envp_node				*export_head;		//linked list of envp
	t_envp_node				*envp_head;		//linked list of envp
	int						exit_status;
	int						sigint_listener;
	char					**list_cmds;
	t_redirection			**list_reds;
	int stin;
	int stout;
	int ppin;
	int ppout;
} t_global_struct;

extern t_global_struct *gstruct;

int     	repl(void);                 // the starting point :  repl = read-eval-print loop
int			tokenize_expand_execute(char *input);    // the starting point
t_token 	*tokenize_input(void);      // for creating the array of tokens from the user input
int     	init_gstruct();  // for initializing the global strcut
int			init_envp(char **envp);
int		envp_list_vars_len(t_envp_node *ptr);
char	**get_envp_arr();
void		free_split(char **list);
t_envp_node	*envp_new_node(char *key, char *value);
void		envp_lst_add_back(t_envp_node *node, t_envp_node **head);
void		envp_delete_node(int pos, t_envp_node **head);
t_envp_node	*envp_find_node(char *key, size_t len, t_envp_node *head);
int			duplicate_list_export();
void		ft_env(void);
void		ft_export_with_args(char **phrase);
void		ft_export_no_args();
void		ft_unest(char **list_keys);
void		ft_pwd(void);
void		ft_echo(char **list_vars);
void		ft_cd(char **list_vars);
void	ft_exit(char	**list_vars);
void		sig_init(int sig, void (*sig_handler)(int));
void		sigint_hander(int sig);
void		sigquit_hander(int sig);
void	sigint_hander_executor(int sig);
char		*rl_replace_line(const char *text, int clear_undo);
char		**ft_split_string(char const *s, char* list);
int			is_part_of_list(char c, char *list);
t_token_lst	*tokenize(char	*input);
int			ft_check_der(char *str);
int			ft_check_pipe(char *str);
void		display_tokens(t_token_lst *token);
// void		expand_variables(t_token_lst *tokens_lst);
void		expand(t_token_lst *tokens_lst);
void		expand_quotes(char **original, t_token_type token_type);
void		expand_variables(char **original, char *copy, t_token_type token_type);
void		expand_variables_handler(char **original, char *copy, int *i, t_token_type token_type);
int			ft_strlcmp(const char *s1, const char *s2);
int			check_str(char *str);
void		expand_exit_status(char **original, char *copy);
char   		 **ft_pipe_insert(char   *input, char    **str);
int			get_variable_len(char *start);
void		cbc_str_join(char **original, char c);
void		create_original_str(char **original);

char		*ft_strdup_file(char	*s);
char		**ft_split_der(char	**str, char *input, char n);
void		ft_lst_token_add_back(t_token_lst **lst, t_token_lst *new);
int			ft_count_str(char	**str);
char		**ft_pipe_insert(char *input, char	**str);
int			ft_count_der(char	**str, char n);
char		*ft_strdup_arg(char	*s);
char		*ft_strdup_der(char	*s);

char	*ft_strtrim(char const *s1, char const *set);
int 	ft_check_space_pipe(char **temp);
char	**ft_args_split(char *str);
char	**ft_der_insert(char	*input, char	**str, char *c);
char	**ft_split_qotes(char *s, char c);


int			ft_check_dub_der2(char	*input, char n);
int			ft_check_mul_pipe(char	*input);
int			ft_check_der(char *str);
int 		ft_check_pipe(char *str);
int			ft_check_mul_der(char	*input, char c);
int			ft_check_der_right(char *str);
int			ft_check_der_left(char *str);
char		**ft_der_insert_2(char	*input, char	**str, char *c, char *a);
void		ft_free_token(char **str);

void		piping_main(t_token_lst *tokens_lst);
void		ft_infile_error(char *infile);
void		ft_outfile_error(char *outfile);
void		ft_excute_error(char *cmd);
char		*path_finder(char *cmd, t_envp_node *envp);
void		ft_error(char *m);
void		cmd_not_found(char **cmd);
void		ft_error_msg(char *m);

// executor stuff
char	*create_envp_value(char *key);
void executor(t_token_lst *token_lst);
char	**create_lst_commands(t_token_lst *token_lst);
t_redirection    **create_lst_redirections(t_token_lst *token_lst);
// t_separated_token	*sep_token_new_node(char *value, t_red_type sep_token_type);
// void	sep_token_add_back(t_separated_token *token, t_red_type sep_token_type);
int		count_commands(t_token_lst *token_lst);
int		count_redirections(t_token_lst *token_lst);

//free
void	free_token_lst();
void	free_envp_nodes_lst();
void	free_cmds_reds_array();
void	free_global_struct();
void	free_all();


void    ex_main(t_token_lst *token1, t_token_lst *token2);

int redirect_out_file_heredoc(char *red);
int redirect_out_file(char *red);
int redirect_in_file(char *red);
int redirect_in_file_append(char *red);

void	cmd_not_found(char **cmd);
void redirect_in_out(t_redirection **list_reds);
int	is_builtin(char	*cmd);
void handle_builtin(char **list_cmds);
int	list_vars_len(char **list_cmds);
int	char_in_str(char *str, char c);
# endif



//docker run -it --rm -v $HOME/Desktop/cursus/tmpminishell:/minishell rhub/ubuntu-gcc

