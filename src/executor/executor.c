#include "../../minishell.h"

void	transforming_token_lst(t_token_lst *token_lst)
{
	int					i;
	t_separated_token	*sep_token;
	t_separated_token	*sep_head;

	i = 0;
	if(!token_lst)
		return ;
	
	printf("num_cmd %d\n", count_commands(token_lst));
	printf("num_red %d\n", count_redirections(token_lst));
}

void executor(t_token_lst *token_lst)
{
	transforming_token_lst(token_lst);
}