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

t_token_lst	*ft_put_intoken(char **str)
{
	t_token_lst	*node;
	t_token_lst	*token;
	char		**tmp;
	int			i;
	int			j;
	int			k;

	k = 1;
	j = 0;
	i = 0;
	token = NULL;
	node = NULL;
	while (i < ft_count_str(str))
	{
		node = malloc(sizeof(t_token_lst));
		node->token = malloc(sizeof(t_token));
		node->next = NULL;
		if (ft_check_pipe(str[i]))
		{
			node->token->args = ft_split(str[i], ' ');
			node->token->type = AST_PIPE;
			node->token->num_args = 0;
			node->token->redirect_fd = NULL;
			node->token->redirect_fname = NULL;
			node->token->com_plus = NULL;
		}
		else if (ft_check_der(str[i]))
		{
			node->token->redirect_fd = ft_strdup(str[i]);
			node->token->com_plus = NULL;
			if (str[i + 1])
			{
				tmp = ft_split_qotes(str[i + 1], ' ');
				node->token->redirect_fname = ft_strdup(tmp[0]);
				while (tmp[k])
					node->token->com_plus = ft_strjoin_min(node->token->com_plus, tmp[k++]);
			}
			else
				node->token->redirect_fname = NULL;
			node->token->args = NULL;
			node->token->num_args = 0;
			i++;
			node->token->type = AST_REDIRECTION;
		}
		else
		{
			node->token->args = ft_split_qotes(str[i], ' ');
			while (node->token->args[j])
				j++;
			node->token->num_args = 0;
			node->token->redirect_fd = NULL;
			node->token->redirect_fname = NULL;
			node->token->com_plus = NULL;
			node->token->type = AST_COMMAND;
		}
		ft_lst_token_add_back(&token, node);
		//free(node);
		i++;
	}
	ft_free_token(str);
	return (token);
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

t_token_lst	*tokenize(char	*input)
{
	t_token_lst	*token;
	char		**temp;

	token = NULL;
	if (ft_check_qoutes(input))
	{
		printf("qoutes problem\n");
		return (0);
	}
	if (ft_check_mul_pipe(input))
	{
		printf("bash: syntax error near unexpected token `|'\n");
		return (0);
	}
	if (ft_check_mul_der(input, '>'))
	{
		printf("bash: syntax error near unexpected token `>>'\n");
		return (0);
	}
	if (ft_check_mul_der(input, '<'))
	{
		printf("bash: syntax error near unexpected token `<<'\n");
		return (0);
	}
	temp = ft_split_qotes(input, '|');
	temp = ft_pipe_insert(input, temp);
	temp = ft_split_der(temp, input);
	token = ft_put_intoken(temp);
	return (token);
}
