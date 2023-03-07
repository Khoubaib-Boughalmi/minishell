# ifndef MINISHELL_H
# define MINISHELL_H

#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>

#include <string.h>
#include<stdio.h>
typedef enum {
	AST_COMMAND,
	AST_PIPE,
	AST_REDIRECTION,
} t_token_type;


typedef struct s_token {
	t_token_type	type;
	char**			args;
	int				num_args;
	char*			redirect_fd;
	char*			redirect_fname;
} t_token;

typedef struct s_token_list {
	t_token				*token;
	struct s_token_list *next;
} t_token_list;

//shared data goes here
typedef struct s_global_struct
{
	char	*src_input;		//pointer to the users source input
	t_token_list *tokens;    	//pointer to the array of tokens
} t_global_struct;

extern t_global_struct *gstruct;



t_token	*ft_tokenization(char	*input);
char	**ft_split(char *s, char c);
char	*ft_strdup(const char *s);
int	ft_strlen(const char *c);

int ft_check_der(char *str);
int ft_check_pipe(char *str);
char *ft_strdup_file(char	*s);
char	**ft_split_der(char	**str);
void	ft_lstadd_back(t_token_list **lst, t_token_list *new);
int ft_count_str(char	**str);
char	**ft_pipe_insert(char	**str);
int ft_count_der(char	**str);
char *ft_strdup_arg(char	*s);
char *ft_strdup_der(char	*s);

# endif