#include "../../minishell.h"

void expand_exit_status(char **original, char *copy)
{
	char	*expanded_exit;
	int		i;

	i = -1;
	if(gstruct->exit_status == 32512)
		gstruct->exit_status = 127;
	if(ft_strlen(copy) > 2)
	{
		expanded_exit = ft_strjoin(ft_itoa(gstruct->exit_status), &(copy[1]));
		while(expanded_exit[++i] && i <= get_variable_len(&(copy[1])))
			cbc_str_join(original, expanded_exit[i]);
	}
	else
	{
		expanded_exit = ft_itoa(gstruct->exit_status);
		while(expanded_exit[++i])
			cbc_str_join(original, expanded_exit[i]);
	}
}
