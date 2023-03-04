# ifndef MINISHELL_H
# define MINISHELL_H

#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>
# include	"libft/libft.h"
# include	"get_next_line/get_next_line.h"

// AST node types
typedef enum {
	AST_COMMAND,     // a command to execute
	AST_PIPE,        // a pipe between two commands
	AST_REDIRECTION, // a redirection of input or output
} t_token_type;

// node structure
typedef struct s_token {
	t_token_type	type; // the type of the token
	char**			args; // the arguments for a command token
	int				num_args; // the number of arguments for a command token
	int				redirect_fd; // the file descriptor to redirect for a redirection token
	char*			redirect_fname; // the filename to redirect to for a redirection token
} t_token;


typedef struct s_envp_node
{
	struct s_envp_node	*next;
	char				*key;
	char				*value;
} t_envp_node;

//shared data goes here
typedef struct s_global_struct
{
	char		*src_input;		//pointer to the users source input
	t_token		*tokens;    	//pointer to the array of tokens
	t_envp_node	*envp_head;
} t_global_struct;

extern t_global_struct *gstruct;

int     	repl(void);                 // the starting point :  repl = read-eval-print loop
void		parse_and_execute(char *input);    // the starting point
t_token 	*tokenize_input(void);      // for creating the array of tokens from the user input
int     	init_gstruct();  // for initializing the global strcut
int			init_envp(char **envp);
void		free_split(char **list);
t_envp_node	*new_envp_node(char *key, char *value);
void		envp_lst_add_back(t_envp_node *node);
void		ft_env(void);
int			ft_export(char *key, char *value);

# endif