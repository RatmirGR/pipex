#include "pipex.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*p;
	size_t			len;
	unsigned char	*s;

	len = nmemb * size;
	p = NULL;
	p = malloc(len);
	if (p != NULL)
	{
		s = (unsigned char *)p;
		while (len--)
			*s++ = (unsigned char)0;
	}
	return (p);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		++i;
	}
	if (c == '\0')
		return ((char *)&s[i]);
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	size_t	i;
	size_t	j;

	if (s1 == 0 || s2 == 0)
		return (NULL);
	p = NULL;
	i = (ft_strlen(s1) + ft_strlen(s2));
	p = (char *)malloc((i + 1) * sizeof(char));
	if (p != NULL)
	{
		i = -1;
		while (s1[++i])
			p[i] = s1[i];
		j = -1;
		while (s2[++j])
		{
			p[i] = s2[j];
			++i;
		}
		p[i] = '\0';
	}
	return (p);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		++i;
	return (i);
}
