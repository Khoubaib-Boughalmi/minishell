/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rediraction_insert.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennatiq <rennatiq@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 21:26:32 by rennatiq          #+#    #+#             */
/*   Updated: 2023/05/06 08:50:23 by rennatiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_der_insert_norm(char	*input, int k)
{
	char	n;

	if (input[k] == '\'' || input[k] == '\"')
	{
		n = input[k++];
		while (!input[k] || input[k] != n)
			k++;
	}
	return (k);
}

void	ft_der_insert_norm2(t_reder_norm *tmp_args, int *i, int *j, char **res)
{
	while (*tmp_args->str)
	{
		res[(*i)++] = ft_strdup(*tmp_args->str);
		while (tmp_args->input[*j])
		{
			*j = ft_der_insert_norm(tmp_args->input, *j);
			if (tmp_args->input[*j] == tmp_args->c[0])
			{
				(*j)++;
				if (tmp_args->input[*j] == tmp_args->c[0])
				{
					(*j)++;
					res[(*i)++] = ft_strdup(tmp_args->c);
				}
				else
					res[(*i)++] = ft_strdup(tmp_args->a);
				break ;
			}
			(*j)++;
		}
		(tmp_args->str)++;
	}
	res[*i] = 0;
}

void	ft_der_insert_norm3(t_reder_norm *tmp_args, int *i, int *j, char **res)
{
	while (tmp_args->input[*j] == ' ')
			(*j)++;
	if (tmp_args->input[*j] == tmp_args->c[0])
	{
		(*j)++;
		if (tmp_args->input[*j] == tmp_args->c[0])
		{
			(*j)++;
			res[(*i)++] = ft_strdup(tmp_args->c);
		}
		else
			res[(*i)++] = ft_strdup(tmp_args->a);
	}
}

char	**ft_der_insert_2(char *input, char **str, char *c, char *a)
{
	char			**res;
	int				i;
	int				j;
	t_reder_norm	tmp_args;

	i = 0;
	j = 0;
	tmp_args.input = input;
	tmp_args.str = str;
	tmp_args.c = c;
	tmp_args.a = a;
	res = malloc((ft_count_str(str) + ft_cout_red(input, c[0]) + 3)
			* sizeof(char *));
	if (!res)
		return (0);
	ft_der_insert_norm3(&tmp_args, &i, &j, res);
	ft_der_insert_norm2(&tmp_args, &i, &j, res);
	free_split(str);
	return (res);
}
