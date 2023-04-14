#include "../../minishell.h"

void	expand_variables(char **original, char	*copy, t_token_type token_type, t_trim trim)
{
	t_envp_node	*tmp;
	char	*expanded_exit;
	char	*trimed;

	int			i;
	int			j;

	tmp = NULL;
	i = 0;
			if(copy[1] == '?')
				expand_exit_status(original, &(copy[1]));
			else if(!copy[1] || copy[1] == ' ' || copy[1] == '|' )
				cbc_str_join(original, '$');
			else
			{
				tmp = envp_find_node(&(copy[1]), get_variable_len(&(copy[1])), g_struct->envp_head);
				if(tmp)
				{
					i = -1;
					if(trim)
					{
						trimed = epur_str(tmp->value);
						while (trimed[++i])
							cbc_str_join(original, trimed[i]);
					}
					else
					{
						while (tmp->value[++i])
							cbc_str_join(original, tmp->value[i]);
					}
				}
				// else
				// 	cbc_str_join(original, '$');
			}
}
