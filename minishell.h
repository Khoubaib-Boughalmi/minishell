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

//shared data goes here
typedef struct s_global_struct
{
	char	*src_input;		//pointer to the users source input
	t_token *tokens;    	//pointer to the array of tokens
} t_global_struct;

extern t_global_struct *gstruct;


int     repl(void);                 // the starting point :  repl = read-eval-print loop
void	parse_and_execute(char *input);    // the starting point
int     init_gstruct(char *input);  // for initializing the global strcut
t_token *tokenize_input(void);      // for creating the array of tokens from the user input

# endif