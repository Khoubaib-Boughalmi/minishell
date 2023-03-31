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

char	**ft_split_qotes(char *s, char c)
{
	int		i;
	int		j;
	int		k;
	char	n;
	char	**resulta;

	j = 0;
	i = -1;
	k = -1;
	if (!s || how_mush_char(s, c) == 0)
		return (0);
	while (*s == ' ')
		s++;
	resulta = (char **)malloc(sizeof(char *) * (how_mush_char(s, c) + 1));
	if (!resulta)
		return (0);
	while (++i <= ft_strlen(s))
	{
		if (s[i] != c && k < 0)
			k = i;
		if (s[i] == '\'' || s[i] == '\"')
		{
			n = s[i];
			i++;
			while (!s[i] || (s[i] != n && s[i] != n))
				i++;
		}
		else if ((s[i] == c || i == ft_strlen(s)) && k >= 0 && j < how_mush_char(s, c) -1)
		{
			resulta[j++] = make_word(s, k, i);
			k = -1;
		}
	}
	resulta[j] = 0;
	return (resulta);
}
