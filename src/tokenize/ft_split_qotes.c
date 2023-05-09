/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_qotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal < kboughal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:31:45 by rennatiq          #+#    #+#             */
/*   Updated: 2023/05/09 21:29:35 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	scep_qoutes(char *s, int i)
{
	char	n;

	if (s[i] == '\'' || s[i] == '\"')
	{
		n = s[i++];
		while (!s[i] || (s[i] != n && s[i] != n))
			i++;
	}
	return (i);
}

static int	how_mush_char(char *s, char c)
{
	int		i;
	int		count;
	char	n;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			n = s[i];
			i++;
			while (!s[i] || (s[i] != n && s[i] != n))
				i++;
		}
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count + 1);
}

static char	*make_word(const char *s, int k, int i)
{
	char	*resulta;
	int		j;

	j = 0;
	resulta = malloc((i - k + 1) * sizeof(char));
	if (!resulta)
		return (0);
	while (k < i)
		resulta[j++] = s[k++];
	resulta[j] = '\0';
	return (resulta);
}

void	ft_split_norm(char *s, char **result, char c)
{
	int		i;
	int		j;
	int		k;

	j = 0;
	i = -1;
	k = -1;
	while (++i <= (int)ft_strlen(s))
	{
		if (s[i] != c && k < 0)
			k = i;
		i = scep_qoutes(s, i);
		if ((s[i] == c || i == (int)ft_strlen(s)) && k >= 0
			&& j < how_mush_char(s, c) - 1)
		{
			result[j++] = make_word(s, k, i);
			k = -1;
		}
	}
	result[j] = 0;
}

char	**ft_split_qotes(char *s, char c)
{
	char	**result;

	if (!s || how_mush_char(s, c) == 0)
		return (0);
	while (*s == ' ')
		s++;
	result = (char **)malloc(sizeof(char *) * (how_mush_char(s, c) + 1));
	if (!result)
		return (0);
	ft_split_norm(s, result, c);
	return (result);
}
