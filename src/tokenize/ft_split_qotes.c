#include "../../minishell.h"

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
	char	*result;
	int		j;

	j = 0;
	result = malloc((i - k + 1) * sizeof(char));
	if (!result)
		return (0);
	while (k < i)
		result[j++] = s[k++];
	result[j] = '\0';
	return (result);
}

char	**ft_split_qotes(char *s, char c)
{
	int		i;
	int		j;
	int		k;
	char	n;
	char	**result;

	j = 0;
	i = -1;
	k = -1;
	if (!s || how_mush_char(s, c) == 0)
		return (0);
	while (*s == ' ')
		s++;
	result = (char **)malloc(sizeof(char *) * (how_mush_char(s, c) + 1));
	if (!result)
		return (0);
	while (++i <= ft_strlen(s))
	{
		if (s[i] != c && k < 0)
			k = i;
		if (s[i] == '\'' || s[i] == '\"')
		{
			n = s[i++];
			while (!s[i] || (s[i] != n && s[i] != n))
				i++;
		}
		else if ((s[i] == c || i == ft_strlen(s)) && k >= 0
				&& j < how_mush_char(s, c) -1)
		{
			result[j++] = make_word(s, k, i);
			k = -1;
		}
	}
	result[j] = 0;
	return (result);
}
