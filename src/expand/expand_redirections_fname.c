/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redirections_fname.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal < kboughal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 21:20:16 by kboughal          #+#    #+#             */
/*   Updated: 2023/05/04 20:17:30 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_split_data(char *str)
{
	int		j;
	int		start;
	int		end;
	char	*tmp;

	j = ft_strlen(str);
	start = get_start(str);
	end = ft_strlen(str);
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

void	check_ambiguous_fname(t_token *token, char **split_words)
{
	int		k;
	int		count;
	char	*tmp;

	k = 0;
	count = 0;
	while (split_words[k])
	{
		tmp = ft_split_data(split_words[k]);
		if (!tmp || tmp[0] == '\0')
			count++;
		k++;
		free(tmp);
	}
	if (count < k - 1)
		set_ambiguous_state(token);
	expand_quotes_red(&(token->redirect_fname));
}

void	expand_and_trim(t_token *token)
{
	char	*rd_fname_copy;

	rd_fname_copy = ft_strdup(token->redirect_fname);
	if (token->redirect_fname)
		free(token->redirect_fname);
	token->redirect_fname = trim_str(rd_fname_copy);
	expand_quotes_red(&(token->redirect_fname));
	if (rd_fname_copy)
		free(rd_fname_copy);
}

char	*copy_redirection_fname(t_token *token)
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
	char	*copy;
	char	**split_words;

	i = 0;
	copy = copy_redirection_fname(token);
	if (expand_redirection_vars(&(token->redirect_fname), copy))
		set_ambiguous_state(token);
	else
	{
		if (token->redirect_fname)
		{
			split_words = ft_split_qotes(token->redirect_fname, ' ');
			if (split_words[1])
				check_ambiguous_fname(token, split_words);
			else
				expand_and_trim(token);
			if (split_words)
				free_split(split_words);
		}
	}
	if (copy)
		free(copy);
}
