#include "pipex.h"

static char	*ft_get_ftext(char *ftext)
{
	char	*p;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (ftext != NULL)
	{
		while (ftext[i] && ftext[i] != '\n')
			++i;
		if (ftext[i] != '\0')
		{
			p = ft_calloc(ft_strlen(ftext) - i + 1, sizeof(char));
			if (p != NULL)
			{
				while (ftext[i++] != '\0')
					p[j++] = ftext[i];
				p[j] = '\0';
				free(ftext);
				return (p);
			}
		}
		free(ftext);
	}
	return (0);
}

static char	*ft_get_line(char *ftext)
{
	char	*pos;
	char	*p;
	size_t	len;

	if (ftext != NULL && *ftext != '\0')
	{
		pos = ft_strchr(ftext, '\n');
		if (pos == NULL)
			len = ft_strlen(ftext);
		else
			len = (size_t)(pos - ftext);
		p = ft_calloc(len + 1, sizeof(char));
		if (p != NULL)
		{
			if (pos != NULL)
				p[len + 1] = '\0';
			while (len--)
				p[len] = ftext[len];
			return (p);
		}
	}
	return (0);
}

static char	*ft_read_file(int fd, char *ftext, char *buf)
{
	ssize_t	count;

	if (ftext == NULL)
		ftext = ft_calloc(1, sizeof(char));
	count = 1;
	while (count > 0 && ft_strchr(ftext, '\n') == NULL)
	{
		count = read(fd, buf, BUFFER_SIZE);
		if (count < 0)
			break ;
		buf[count] = '\0';
		ftext = ft_strjoin(ftext, buf);
	}
	return (ftext);
}

char	*get_next_line(int fd)
{
	char		*buf;
	char		*line;
	static char	*ftext;

	if (fd >= 0 && BUFFER_SIZE > 0)
	{
		buf = NULL;
		buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (buf != NULL)
		{
			ftext = ft_read_file(fd, ftext, buf);
			line = ft_get_line(ftext);
			ftext = ft_get_ftext(ftext);
			free(buf);
			buf = NULL;
			return (line);
		}
	}
	return (0);
}
