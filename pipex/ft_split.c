#include "pipex.h"

static size_t	ft_get_countw(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i + 1] && s[i] == c)
			++i;
		if (s[i] && s[i] != c)
		{
			++count;
			while (s[i + 1] && s[i + 1] != c)
				++i;
		}
		++i;
	}
	return (count);
}

static char	*ft_get_word(char const *s, size_t len)
{
	size_t	i;
	char	*p;

	p = NULL;
	p = (char *)malloc((len + 1) * sizeof(char));
	if (p != NULL)
	{
		i = 0;
		while (i < len)
		{
			p[i] = s[i];
			++i;
		}
		p[i] = '\0';
	}
	return (p);
}

static void	ft_get_pos(char const *s, size_t len, char c, char **pp)
{
	size_t	wlen;
	size_t	pos;
	size_t	i;

	i = -1;
	while (++i < len)
	{
		wlen = 0;
		pos = 0;
		while (s[i] == c)
			++i;
		if (s[i] == '\0')
			break ;
		if (s[i] && s[i] != c)
		{
			pos = i;
			while (s[i] && s[i] != c)
			{
				++wlen;
				++i;
			}
			*pp++ = ft_get_word(&s[pos], wlen);
		}
	}
	*pp = 0;
}

char	**ft_split(char const *s, char c)
{
	char	**pp;
	size_t	len;

	pp = NULL;
	if (s != NULL)
	{
		pp = (char **)malloc((ft_get_countw(s, c) + 1) * sizeof(char *));
		len = ft_strlen(s);
		if (pp != NULL)
			ft_get_pos(s, len, c, pp);
	}
	return (pp);
}
