#include "../../minishell.h"

static size_t	ft_word_count(char const *str, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		
		while (str[i] && str[i] == c)
			i++;		
		if(str[i] && str[i] != c)
			count++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (count);
}

static size_t	ft_word_len(char const *str, char c)
{
	size_t	count;

	count = 0;
	while (str[count] != '\0' && str[count] != c && str[count] != '\"' && str[count] != '\'')
		count++;
	return (count);
}

static char	*ft_copy(char const *s, char c, int *i)
{
	int		word_len;
	char	*ptr;
	int		j;

	word_len = ft_word_len(&s[*i], c);
	ptr = (char *)malloc(sizeof(char) * (word_len + 1));
	if (!ptr)
		return (NULL);
	j = 0;
	while (j < word_len)
	{
		ptr[j++] = s[*i];
		*i += 1;
	}
	ptr[j] = '\0';
	return (ptr);
}


int	 count_chars_in_quotes(char *str, int start)
{
	int	i;

	i = 0;
	while (str[start] && str[start] != '\"' && str[start] != '\'')
	{
		start++;
		i++;
	}
	return (i);
}

char	**split_redirection_word(char *s, char c)
{
	int		i;
	int		j;
	int		k;
	char	**ptr;

	i = 0;
	k = 0;
	if(!s)
		return (0);
	ptr = (char **)malloc((ft_word_count(s, c) + 1) * sizeof(char *));
	if (!ptr)
		return (NULL);
	printf("count %d\n", ft_word_count(s, c));
	// while (s[i] != '\0')
	// {
	// 	// if(s[i] == '\"' || s[i] == '\'')
	// 	// {
	// 	// 	i++;
	// 	// 	j = -1;
	// 	// 	ptr[k] = (char *)malloc(sizeof(char) * (count_chars_in_quotes(s, i) + 1));
	// 	// 	while (s[i] && s[i] != '\"'  && s[i] != '\'')
	// 	// 	{
	// 	// 		ptr[k][++j] = s[i];
	// 	// 		i++;
	// 	// 	}
	// 	// 	ptr[k][j + 1] = '\0';
	// 	// 	if(s[i] == '\"' || s[i] == '\'')
	// 	// 	{
	// 	// 		k++;
	// 	// 		i++;
	// 	// 	}
	// 	// }
	// 	while (s[i] == c && s[i] != '\0' && s[i] != '\"' && s[i] != '\'')
	// 		i++;
	// 	if (s[i] != '\0')
	// 	{
	// 		ptr[k] = ft_copy(s, c, &i);
	// 		if (!ptr[k])
	// 			return (ft_free(ptr, k));
	// 		k++;
	// 	}
	// }
	ptr[k] = 0;
	return (ptr);
}
