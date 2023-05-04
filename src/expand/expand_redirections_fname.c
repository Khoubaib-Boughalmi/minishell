/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redirections_fname.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal < kboughal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 21:20:16 by kboughal          #+#    #+#             */
/*   Updated: 2023/05/04 19:22:05 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_split_data(char *str)
{
	int		j;
	int		i;
	int		start;
	int		end;
	char	*tmp;

	i = 0;
	start = 0;
	end = ft_strlen(str);
	while (str[i])
	{
		if (str[i] && (str[i] != '\"' && str[i] != '\''))
			break ;
		if (str[i + 1] && (str[i] == '\"' || str[i] == '\'') \
		&& str[i + 1] == str[i])
			start = i + 2;
		i += 2;
	}
	j = ft_strlen(str);
	while (j > 0)
	{
		if (str[j] && (str[j] != '\"' || str[j] != '\''))
			break ;
		if (str[j - 1] && (str[j] == '\"' || str[j] == '\'') \
		&& str[j - 1] == str[j])
			end = j - 1;
		j--;
	}
	tmp = ft_substr(str, start, end - start);
	return (tmp);
}

char	*init_copy_rd(t_token *token)
{
	char	*copy;
	
	copy = (char *)malloc(sizeof(char) * ft_strlen(token->redirect_fname) + 1);
	ft_strlcpy(copy, token->redirect_fname, \
	ft_strlen(token->redirect_fname) + 1);
	copy[ft_strlen(token->redirect_fname)] = '\0';
	ft_memset(token->redirect_fname, 0, ft_strlen(token->redirect_fname));
	free(token->redirect_fname);
	token->redirect_fname = NULL;
	return (copy);
}

void	expand_redirection_fname(t_token *token)
{
	int		i;
	int		k;
	int		count;
	char	*copy;
	char	**split_words;
	char	*tmp;
	char	*rd_fname_copy;

	i = 0;
	copy = (char *)malloc(sizeof(char) * ft_strlen(token->redirect_fname) + 1);
	ft_strlcpy(copy, token->redirect_fname, \
	ft_strlen(token->redirect_fname) + 1);
	copy[ft_strlen(token->redirect_fname)] = '\0';
	ft_memset(token->redirect_fname, 0, ft_strlen(token->redirect_fname));
	free(token->redirect_fname);
	token->redirect_fname = NULL;
		if (expand_redirection_vars(&(token->redirect_fname), copy))
	{
		token->redirect_error = AMBIGUOUSERR;
		g_struct->exit_status = 1;
	}
	else
	{
		i = 0;
		if (token->redirect_fname)
		{
			split_words = ft_split_qotes(token->redirect_fname, ' ');
			if (split_words[1])
			{
				k = 0;
				count = 0;
				while (split_words[k])
				{
					tmp = ft_split_data(split_words[k]);
					if (!tmp || tmp[0] == '\0')
						count++;
					k++;
				}
				if (count < k - 1)
				{
					token->redirect_error = AMBIGUOUSERR;
					g_struct->exit_status = 1;
				}
				expand_quotes_red(&(token->redirect_fname));
			}
			else
			{
				rd_fname_copy = ft_strdup(token->redirect_fname);
				if (token->redirect_fname)
					free(token->redirect_fname);
				token->redirect_fname = trim_str(rd_fname_copy);
				expand_quotes_red(&(token->redirect_fname));
				if (rd_fname_copy)
					free(rd_fname_copy);
			}
			if (split_words)
				free_split(split_words);
		}
	}
	if (copy)
		free(copy);
}
