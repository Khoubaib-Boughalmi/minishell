#include "../../minishell.h"

int	count_split_str(char	**arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

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
					if(trim == TRIM)
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



void	expand_variables_special(char **original, char	*copy, t_token_type token_type, t_trim trim, char ***args_lst, int *pos)
{
	t_envp_node	*tmp;
	char	*expanded_exit;
	char	*trimed;
	int			i;
	int			j;
	int			x;
	int			y;

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
					if(trim == SPECIAL)
					{
						char **split_tmp = ft_split(tmp->value, ' ');
						char **new_args_lst;
						if(count_split_str(split_tmp) > 1)
						{
							x = 0;
							y = 0;
							new_args_lst = (char **)malloc(sizeof(char *) * (count_split_str(*args_lst) + count_split_str(split_tmp) + 3));
							while ((*args_lst)[y] && x < *pos)
							{
								new_args_lst[x] = ft_strdup((*args_lst)[y]);
								ft_printf("args1: %s\n", new_args_lst[x]);
								x++;
								y++;
							}
							int z = 0;
							while (split_tmp[z])
							{
								new_args_lst[x] = ft_strdup(split_tmp[z]);
								ft_printf("args2: %s\n", new_args_lst[x]);
								x++;
								z++;
							}
							printf("pos : %d %d\n", x, *pos);
							*pos += count_split_str(split_tmp);
							y +=  count_split_str(split_tmp) - 1;
							while ((*args_lst)[y])
							{
								new_args_lst[x] = ft_strdup((*args_lst)[y]);
								ft_printf("args3: %s\n", new_args_lst[x]);
								y++;
								x++;
							}
							new_args_lst[0] = "echo";
							// new_args_lst[x] = NULL;
							free(*args_lst);
							*args_lst = new_args_lst;
							printf("new: %s\n", new_args_lst[0]);
						}
						else
						{
							i = -1;
							while (tmp->value[++i])
								cbc_str_join(original, tmp->value[i]);
						}
						x = 0;
						while ((*args_lst)[x])
						{
							ft_printf("tmppppp: %s\n", (*args_lst)[x]);
							x++;
						}
					}
					else
					{

					if(trim == TRIM)
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
				}
				// else
				// 	cbc_str_join(original, '$');
			}
}
