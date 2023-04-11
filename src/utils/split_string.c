
#include "../../minishell.h"

static size_t	ft_word_count(char const *str, char *list)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && is_part_of_list(str[i], list))
			i++;
		if (str[i] != '\0')
			count++;
		while (str[i] != '\0' && !is_part_of_list(str[i], list))
			i++;
		while (str[i] != '\0' && is_part_of_list(str[i], list))
			i++;
	}
	return (count);
}

static size_t	ft_word_len(char const *str, char *list)
{
	size_t	count;

	count = 0;
	while (str[count] != '\0' && !is_part_of_list(str[count], list))
		count++;
	return (count);
}

static char	*ft_copy(char const *s, char *list, int *i)
{
	int		word_len;
	char	*ptr;
	int		j;

	word_len = ft_word_len(&s[*i], list);
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

static char	**ft_free(char **ptr, int k)
{
	while (k--)
		free(ptr[k]);
	free(ptr);
	return (NULL);
}

char	**ft_split_string(char const *s, char* list)
{
	int		i;
	int		k;
	char	**ptr;

	i = 0;
	k = 0;
	ptr = (char **)malloc((ft_word_count(s, list) + 1) * sizeof(char *));
	if (!ptr)
		return (NULL);
	while (s[i] != '\0')
	{
		while (is_part_of_list(s[i], list) && s[i] != '\0')
			i++;
		if (s[i] != '\0')
		{
			ptr[k] = ft_copy(s, list, &i);
			if (!ptr[k])
				return (ft_free(ptr, k));
			k++;
		}
	}
	ptr[k] = 0;
	return (ptr);
}