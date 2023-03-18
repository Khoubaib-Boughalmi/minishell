#include "../../minishell.h"

void	free_split(char **list)
{
	int	i;

	i = -1;
	while (list[++i])
		free(list[i]);
	free(list);
}

int	is_part_of_list(char c, char *list)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(list))
	{
		if(list[i] == c)
			return (1);
		i++;
	}
	return (0);
}


int	ft_strlcmp(const char *s1, const char *s2)
{
	size_t	i;
	size_t	l1;
	size_t	l2;

	if (!s1 || !s2)
		return (0);
	i = 0;
	l1 = get_variable_len((char *)s1);
	l2 = get_variable_len((char *)s2);
	if(l1 != l2)
		return (1);
	while (s1[i] == s2[i] && s1[i] != '\0')
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	check_str(char *str)
{
	if(!str || !str[0] || str[0] == '\n')
		return (0);
	return (1);
}

//this function find the key you are looking for in envp and creates a new string with the value of the key 
char	*create_envp_value(char *key)
{
	char		*full_path;
	t_envp_node	*envp_ptr;

	envp_ptr = gstruct->envp_head;
	full_path = NULL;
	while (envp_ptr)
	{
		if(!strncmp(key, envp_ptr->key, 4))
		{
			full_path = (char *)malloc(sizeof(char) * ft_strlen(envp_ptr->value) + 1);
			ft_strlcpy(full_path, envp_ptr->value, ft_strlen(envp_ptr->value) + 1);
			break;
		}
		envp_ptr = envp_ptr->next;
	}
	return (full_path);
}