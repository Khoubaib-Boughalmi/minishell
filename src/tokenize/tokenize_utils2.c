/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennatiq <rennatiq@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 21:13:04 by rennatiq          #+#    #+#             */
/*   Updated: 2023/05/12 12:31:50 by rennatiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_check_pipe(char *str)
{
	int	j;

	j = 0;
	if (str[0] == '|')
		return (1);
	return (0);
}

void	ft_lst_token_add_back(t_token_lst **lst, t_token_lst *new)
{
	t_token_lst	*ptr;

	ptr = *lst;
	if (!new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
}

int	ft_count_der(char	**str, char n)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] == n)
			{
				count++;
				while (str[i][j] && str[i][j] == n)
					j++;
			}
			else
				j++;
		}
		i++;
	}
	return (count * 2);
}
