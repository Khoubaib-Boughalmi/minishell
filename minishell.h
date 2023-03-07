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
} t_global_struct;

extern t_global_struct *gstruct;

int     	repl(void);                 // the starting point :  repl = read-eval-print loop
void		parse_and_execute(char *input);    // the starting point
t_token 	*tokenize_input(void);      // for creating the array of tokens from the user input
int     	init_gstruct();  // for initializing the global strcut
int			init_envp(char **envp);
void		free_split(char **list);
t_envp_node	*envp_new_node(char *key, char *value);
void		envp_lst_add_back(t_envp_node *node);
void		envp_delete_node(int pos);
char		*envp_find_node(char *key);
int			ft_env(void);
int			ft_export(char *key, char *value);
int			ft_unest(char *key);
int			ft_pwd(void);
int			ft_echo(char *str);
int			ft_cd(char *str);
void		sig_init(int sig, void (*sig_handler)(int));
void		sigint_hander(int sig);
void		sigquit_hander(int sig);
char		*rl_replace_line(const char *text, int clear_undo);
char		**ft_split_string(char const *s, char* list);
int			is_part_of_list(char c, char *list);
t_token_lst	*tokenizer(char	*input);
int			ft_check_der(char *str);
int			ft_check_pipe(char *str);
char		*ft_strdup_file(char	*s);
char		**ft_split_der(char	**str);
void		ft_lst_token_add_back(t_token_lst **lst, t_token_lst *new);
int			ft_count_str(char	**str);
char		**ft_pipe_insert(char	**str);
int			ft_count_der(char	**str);
char		*ft_strdup_arg(char	*s);
char		*ft_strdup_der(char	*s);

# endif