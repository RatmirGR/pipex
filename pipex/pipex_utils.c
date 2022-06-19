#include "pipex.h"

int	ft_line_len(char **line)
{
	int	i;

	i = 0;
	while (line[i] != NULL)
		i++;
	return (i);
}

void	ft_print_error(t_list *config, char *desc, char *name)
{
	write(2, "pipex: ", 7);
	write(2, desc, ft_strlen(desc));
	write(2, ": ", 2);
	write(2, name, ft_strlen(name));
	write(2, "\n", 1);
	ft_all_free(config);
	exit(1);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] > s2[i])
			return (1);
		if (s1[i] < s2[i])
			return (-1);
		++i;
	}
	if (s1[i] != '\0')
		return (1);
	if (s2[i] != '\0')
		return (-1);
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*p1;
	unsigned char	*p2;

	i = 0;
	p1 = (unsigned char *)s1;
	p2 = (unsigned char *)s2;
	while ((p1[i] || p2[i]) && (i < n))
	{
		if (p1[i] != p2[i])
			return (p1[i] - p2[i]);
		++i;
	}
	return (0);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	i;

	if (s == '\0')
		return (NULL);
	i = ft_strlen(s);
	if (start > i)
		len = 0;
	else if (len > i)
		len = i;
	p = NULL;
	p = (char *)malloc((len + 1) * sizeof(char));
	if (p != NULL)
	{
		i = 0;
		while (len--)
		{
			p[i] = s[start];
			++i;
			++start;
		}
		p[i] = '\0';
	}
	return (p);
}
