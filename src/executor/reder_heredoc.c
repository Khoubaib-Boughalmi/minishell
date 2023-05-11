/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reder_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennatiq <rennatiq@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 20:08:52 by rennatiq          #+#    #+#             */
/*   Updated: 2023/05/10 19:23:49 by rennatiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	redirect_heredoc(char *str, char *new_str, int *pip)
{
	int		i;
	int		j;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			str[ft_strlen(str) - 1] = '\0';
			expand_variables(&new_str, str + i, NOTRIM);
			if (new_str)
			{
				j = 0;
				while (new_str[j])
					ft_putchar_fd(new_str[j++], pip[1]);
				i += get_variable_len(str + i + 1);
			}
			free(new_str);
			new_str = NULL;
		}
		else
			ft_putchar_fd(str[i], pip[1]);
		i++;
	}
	ft_putchar_fd('\n', pip[1]);
}

void	redirect_heredoc_norm(char *new_str, char *red, char *str, int *pip)
{
	if (char_in_str(str, '$') && !char_in_str(red, '\"')
		&& !char_in_str(red, '\''))
		redirect_heredoc(str, new_str, pip);
	else
		ft_putstr_fd(str, pip[1]);
	free(str);
	str = NULL;
}

void	redirect_out_file_heredoc_norm(char *str, char *new_red, char *red_cpy)
{
	if (red_cpy)
		free(red_cpy);
	if (new_red)
		free(new_red);
	free(str);
}

int	redirect_out_file_heredoc(char *red)
{
	int		pip[2];
	char	*str;
	char	*new_str;
	char	*red_cpy;
	char	*new_red;

	new_str = NULL;
	pipe(pip);
	dup2(g_struct->ppin, 0);
	new_red = ft_strjoin(red, "\n");
	red_cpy = ft_strdup(new_red);
	expand_quotes_red(&red_cpy);
	str = get_next_line(0);
	while (str)
	{
		if (!ft_strlcmp(red_cpy, str))
			break ;
		redirect_heredoc_norm(new_str, new_red, str, pip);
		str = get_next_line(0);
	}
	redirect_out_file_heredoc_norm(str, new_red, red_cpy);
	close(pip[1]);
	dup2(g_struct->stin, 0);
	return (pip[0]);
}
