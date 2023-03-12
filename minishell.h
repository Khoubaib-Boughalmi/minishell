# ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <signal.h>
#include <termios.h>
# include <unistd.h>
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"

// AST node types
typedef enum {
	AST_COMMAND,     // a command to execute
	AST_PIPE,        // a pipe between two commands
	AST_REDIRECTION, // a redirection of input or output
} t_token_type;

// node structure
typedef struct s_token {
	t_token_type	type; // the type of the token
	char			**args; // the arguments for a command token
	int				num_args; // the number of arguments for a command token
	char			*redirect_fd; // the file descriptor to redirect for a redirection token
	char			*redirect_fname; // the filename to redirect to for a redirection token
	int				exit_status;
} t_token;


typedef struct s_envp_node
{
	struct s_envp_node	*next;
	char				*key;
	char				*value;
} t_envp_node;

typedef struct s_token_lst {
	t_token				*token;
	struct s_token_lst *next;
} t_token_lst;

//shared data goes here
typedef struct s_global_struct
{
	char		*src_input;		//pointer to the users source input
	t_token_lst	*tokens_head;	//linked list of tokens
	t_envp_node	*envp_head;		//linked list of envp
	int			sigint_listener;
	int			exit_status;
} t_global_struct;

extern t_global_struct *gstruct;

int     	repl(void);                 // the starting point :  repl = read-eval-print loop
int			tokenize_expand_execute(char *input);    // the starting point
t_token 	*tokenize_input(void);      // for creating the array of tokens from the user input
int     	init_gstruct();  // for initializing the global strcut
int			init_envp(char **envp);
void		free_split(char **list);
t_envp_node	*envp_new_node(char *key, char *value);
void		envp_lst_add_back(t_envp_node *node);
void		envp_delete_node(int pos);
t_envp_node	*envp_find_node(char *key, size_t len);
void		ft_env(void);
void		ft_export(char *key, char *value);
void		ft_unest(char *key);
void		ft_pwd(void);
void		ft_echo(char *str);
void		ft_cd(char *str);
void		sig_init(int sig, void (*sig_handler)(int));
void		sigint_hander(int sig);
void		sigquit_hander(int sig);
char		*rl_replace_line(const char *text, int clear_undo);
char		**ft_split_string(char const *s, char* list);
int			is_part_of_list(char c, char *list);
t_token_lst	*tokenize(char	*input);
int			ft_check_der(char *str);
int			ft_check_pipe(char *str);
void		display_tokens(t_token_lst *token);
// void		expand_variables(t_token_lst *tokens_lst);
void		expand(t_token_lst *tokens_lst);
void		expand_quotes(char *arg, t_token_type token_type);
void		expand_variables(char *key, t_token_type token_type);
int			ft_strlcmp(const char *s1, const char *s2);
int			check_str(char *str);
void		expand_exit_status(t_token_lst *tokens_lst, int i);
char    **ft_pipe_insert(char   *input, char    **str);
int		get_key_len(char *start);


char		*ft_strdup_file(char	*s);
char		**ft_split_der(char	**str, char *input);
void		ft_lst_token_add_back(t_token_lst **lst, t_token_lst *new);
int			ft_count_str(char	**str);
char		**ft_pipe_insert(char *input, char	**str);
int			ft_count_der(char	**str);
char		*ft_strdup_arg(char	*s);
char		*ft_strdup_der(char	*s);

char	*ft_strtrim(char const *s1, char const *set);
int	ft_check_mul_pipe(char	*input);
int ft_check_space_pipe(char **temp);
char	**ft_args_split(char *str);
int	ft_check_mul_der(char	*input, char c);
char	**ft_der_insert(char	*input, char	**str, char *c);
char	**ft_split_qotes(char *s, char c);


# endif

