/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennatiq <rennatiq@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 17:01:29 by rennatiq          #+#    #+#             */
/*   Updated: 2023/04/07 17:38:00 by rennatiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strjoin_min(char *s1, char *s2)
{
	char		*str;
	int			i;
	int			j;

	if (!s1)
	{
		s1 = (char *)malloc(sizeof(char));
		s1[0] = '\0';
	}
	if (!s2)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!str)
		return (NULL);
	i = -1;
	while (s1 && s1[++i] != '\0')
		str[i] = s1[i];
	j = 0;
	str[i++] = ' ';
	while (s2 && s2[j] != '\0')
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	return (str);
}

int	ft_check_qoutes(char *input)
{
	int		i;
	char	n;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			n = input[i];
			i++;
			while (!input[i] || input[i] != n)
			{
				i++;
				if (!input[i])
					return (1);
			}
		}
		i++;
	}
	return (0);
}

t_red_type	redtype(char *str)
{
	if (!ft_strlcmp("<<", str))
		return (HEREDOC);
	else if (!ft_strlcmp(">>", str))
		return (APPEND);
	else if (!ft_strlcmp("<", str))
		return (INPUT);
	else
		return (OUTPUT);
}

t_token_lst	*tokenize(char	*input)
{
	t_token_lst	*token;
	char		**temp;

	token = NULL;
	temp = ft_split_qotes(input, '|');
	temp = ft_pipe_insert(input, temp);
	temp = ft_split_der(temp, input, '>');
	temp = ft_split_der(temp, input, '<');
	token = ft_put_intoken(temp);
	return (token);
}
