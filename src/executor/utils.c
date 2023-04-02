#include "../../minishell.h"

int	count_commands(t_token_lst *token_lst)
{
	int	i;
	int	count;

	count = 0;
	while(token_lst && token_lst->token->type != AST_PIPE)
	{
		i = 0;
		if(token_lst->token->type == AST_COMMAND)
		{
			while (token_lst->token->args[i])
				i++;
		}
		count += i;
		token_lst = token_lst->next;
	}
	return (count);
}

int	count_redirections(t_token_lst *token_lst)
{
	int	count;

	count = 0;
	while(token_lst && token_lst->token->type != AST_PIPE)
	{
		if(token_lst->token->type == AST_REDIRECTION)
			count ++;
		token_lst = token_lst->next;
	}
	return (count);
}

char	**get_envp_arr()
{
	int			i;
	int			j;
	int			key_len;
	int			value_len;
	int			len;
	t_envp_node	*ptr;
	char			*str;
	char			**envp_str;

	i = 0;
	ptr = gstruct->envp_head;
	len = envp_list_vars_len(ptr);
	if(!len)
		return NULL;
	envp_str = (char **)malloc(sizeof(char *) * len + 1);
	if(!envp_str)
		return NULL;
	envp_str[len] = 0;
	while (ptr)
	{
		j = 0;
		envp_str[i] = ft_strdup(ptr->key);
		envp_str[i] = ft_strjoin(envp_str[i], "=");
		envp_str[i] = ft_strjoin(envp_str[i], ptr->value);
		ptr = ptr->next;
		i++;
	}
	return (envp_str);
}

// t_separated_token	*sep_token_new_node(char *value, t_red_type sep_token_type)
// {
// 	t_separated_token	*token;

// 	token = (t_separated_token *)malloc(sizeof(t_separated_token));
// 	if(!token)
// 		return (0);
// 	token->value = (char *)malloc(ft_strlen((char *)value) + 1);
// 	token->type = sep_token_type;
// 	if(!token->value)
// 		return (0);
// 	ft_strlcpy(token->value, value, ft_strlen((char *)value) + 1);
// 	token->next = NULL;
// 	return (token);
// }

// void	sep_token_add_back(t_separated_token *token, t_red_type sep_token_type)
// {
// 	t_separated_token	*command_lst;
// 	t_separated_token	*redirection_lst;

// 	command_lst = gstruct->seperated_token_arr[0];
// 	redirection_lst = gstruct->seperated_token_arr[1];
// 	if(sep_token_type == COMMAND)
// 	{
// 		if(!gstruct->seperated_token_arr[0])
// 			gstruct->seperated_token_arr[0] = token;
// 		else
// 		{
// 			while (command_lst->next)
// 				command_lst = command_lst->next;
// 			command_lst->next = token;
// 		}
// 	}
// 	else
// 	{
// 		if(!gstruct->seperated_token_arr[1])
// 			gstruct->seperated_token_arr[1] = token;
// 		else
// 		{
// 			while (redirection_lst->next)
// 				redirection_lst = redirection_lst->next;
// 			redirection_lst->next = token;
// 		}
// 	}
// }
